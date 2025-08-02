#pragma once
#include <memory>
#include <string>
#include <type_traits>
#include "resources/IResourceManager.hpp"
#include "resources/Model.hpp"
#include "utilities/MathHelper.hpp"
#include "utilities/IOC.hpp"
#include "utilities/Logger.hpp"
#include "filesystem/IFileSystem.hpp"
#include "filesystem/File.hpp"
#include "resources/Material.hpp"

using namespace std;
using namespace Utilities;

namespace Engine
{
	class ModelLoaderBase 
	{
	public:
		ModelLoaderBase() 
		: mResourceManager(IOCContainer::instance().resolve_type<IResourceManager>())
		, mFileSystem(IOCContainer::instance().resolve_type<IFileSystem>()) {

		}
		
	protected:	
		virtual void parseFaces(FILE* fileHandle) = 0;

		void parse(FILE* fileHandle) {
			char buffer[100];

			while (!feof(fileHandle))
			{
				fscanf(fileHandle, "%s ", buffer);
				auto instruction = string(buffer);
				
				if(instruction == "v")
				{
					parseVertex(fileHandle);
				}
				else if(instruction == "vt")
				{
					parseUVs(fileHandle);
				}
				else if(instruction == "vn")
				{
					parseNormal(fileHandle);
				}
				else if(instruction == "f")
				{
					parseFaces(fileHandle);
				}
				else if(instruction == "mtllib")
				{
					parseMaterial(fileHandle);
				}
			}
		}

	private:
		void parseVertex(FILE* fileHandle) {
			const int MAX_VERTICES = 9;
			float vertex[MAX_VERTICES];
			int i = 0;
			while(i < MAX_VERTICES && fscanf(fileHandle, "%f ", &vertex[i]) > 0) {
				i++;
			}
			debuglog << "Read vertex!" << vertex[0] << "," << vertex[1] << "," << vertex[2] << std::endl;
			mVerts.emplace_back(Vector3{vertex[0],vertex[1],vertex[2]});
		}

		void parseUVs(FILE* fileHandle) {
			debuglog << "Reading texture coordinate!" << std::endl;
			float u, v;
			fscanf(fileHandle, "%f %f", &u, &v);
			mUVs.emplace_back(Vector2{u,v});
		}

		void parseNormal(FILE* fileHandle) {
			debuglog << "Reading vertex normal!" << std::endl;
			float x, y, z;
			fscanf(fileHandle, "%f ", &x);
			fscanf(fileHandle, "%f ", &y);
			fscanf(fileHandle, "%f ", &z);
			mNormals.emplace_back(Vector3{x,y,z});
		}

		void parseMaterial(FILE* fileHandle) {
			char buffer[100];
			debuglog << "Reading material!" << std::endl;
			fscanf(fileHandle, "%s", buffer);
			auto materialFilename = string(buffer);
			mResourceManager->loadMaterial(materialFilename);
			mMaterial = mResourceManager->getMaterial(materialFilename);
		}

	protected:
		std::shared_ptr<IResourceManager> mResourceManager;
		std::shared_ptr<IFileSystem> mFileSystem;
		std::vector<Vector3> mVerts;
		std::vector<Vector3> mNormals;
		std::vector<Vector2> mUVs;
		Material mMaterial;
	};

	class VertexPositionTextureModelLoader : protected ModelLoaderBase
	{
	public:

		std::shared_ptr<Model<VertexPositionTexture>> loadAndParse(const std::string &fileName) {
			const auto file = mFileSystem->loadFile(std::string("models/" + fileName), false);
			debuglog << "[ModelLoader::loadModel] Loading model" << endl;
			if (file && file->isOpen())
			{
				auto fileHandle = file->get();
				parse(fileHandle);
			}
			return make_shared<Model<VertexPositionTexture>>(mVertices, mMaterial);
		}

	protected:
		virtual void parseFaces(FILE* fileHandle) {
			const int MAX_FACES = 4;
			int v[MAX_FACES], u[MAX_FACES];
			int i = 0;
			while(i < MAX_FACES && fscanf(fileHandle, "%i/%i ", &v[i], &u[i]) > 0)
				i++;
			if(i >= 3) {
				mVertices.emplace_back(VertexPositionTexture(mVerts[v[0]-1], mUVs[u[0]-1]));
				mVertices.emplace_back(VertexPositionTexture(mVerts[v[1]-1], mUVs[u[1]-1]));
				mVertices.emplace_back(VertexPositionTexture(mVerts[v[2]-1], mUVs[u[2]-1]));
			}
			if(i == 4) {
				mVertices.emplace_back(VertexPositionTexture(mVerts[v[0]-1], mUVs[u[0]-1]));
				mVertices.emplace_back(VertexPositionTexture(mVerts[v[2]-1], mUVs[u[2]-1]));
				mVertices.emplace_back(VertexPositionTexture(mVerts[v[3]-1], mUVs[u[3]-1]));
			}
		}

	private:
		std::vector<VertexPositionTexture> mVertices;
	};

	class VertexPositionNormalTextureModelLoader : protected ModelLoaderBase
	{
	public:

		std::shared_ptr<Model<VertexPositionNormalTexture>> loadAndParse(const std::string &fileName) {
			const auto file = mFileSystem->loadFile(std::string("models/" + fileName), false);
			debuglog << "[ModelLoader::loadModel] Loading model" << endl;
			if (file && file->isOpen())
			{
				auto fileHandle = file->get();
				parse(fileHandle);
			}
			return make_shared<Model<VertexPositionNormalTexture>>(mVertices, mMaterial);
		}

	protected:
		virtual void parseFaces(FILE* fileHandle) {
			const int MAX_FACES = 4;
			int v[MAX_FACES], n[MAX_FACES], u[MAX_FACES];
			int i = 0;
			while(i < MAX_FACES && fscanf(fileHandle, "%i/%i/%i ", &v[i], &u[i], &n[i]) > 0)
				i++;
			if(i >= 3) {
				mVertices.emplace_back(VertexPositionNormalTexture(mVerts[v[0]-1], mNormals[n[0]-1], mUVs[u[0]-1]));
				mVertices.emplace_back(VertexPositionNormalTexture(mVerts[v[1]-1], mNormals[n[1]-1], mUVs[u[1]-1]));
				mVertices.emplace_back(VertexPositionNormalTexture(mVerts[v[2]-1], mNormals[n[2]-1], mUVs[u[2]-1]));
			}
			if(i == 4) {
				mVertices.emplace_back(VertexPositionNormalTexture(mVerts[v[0]-1], mNormals[n[0]-1], mUVs[u[0]-1]));
				mVertices.emplace_back(VertexPositionNormalTexture(mVerts[v[2]-1], mNormals[n[2]-1], mUVs[u[2]-1]));
				mVertices.emplace_back(VertexPositionNormalTexture(mVerts[v[3]-1], mNormals[n[3]-1], mUVs[u[3]-1]));
			}
		}

	private:
		std::vector<VertexPositionNormalTexture> mVertices;
	};
}
