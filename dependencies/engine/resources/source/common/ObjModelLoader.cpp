#include "resources/ObjModelLoader.hpp"
#include "resources/IResourceManager.hpp"
#include "resources/Model.hpp"
#include "utilities/MathHelper.hpp"
#include "utilities/IOC.hpp"
#include "utilities/Logger.hpp"
#include "filesystem/IFileSystem.hpp"
#include "filesystem/File.hpp"
#include <vector>

using namespace std;
using namespace Engine;
using namespace Utilities;

shared_ptr<Model> ObjModelLoader::loadModel(const std::string &fileName)
{
    auto fileSystem = IOCContainer::instance().resolve<IFileSystem>();
    auto resourceManager = IOCContainer::instance().resolve<IResourceManager>();
    std::vector<Vector3> verts;
    std::vector<Vector3> normals;
    std::vector<Vector2> uvs;
    std::vector<VertexPositionNormalTexture> vertices;
    const auto file = fileSystem->loadFile(std::string("models/" + fileName), false);
    Texture2D modelTexture;
    debuglog << "[ModelLoader::loadModel] Loading model" << endl;
    if (file && file->isOpen())
    {
        auto fileHandle = file->get();
        char buffer[100];
        // read header
        // fscanf(fileHandle, "%s,", buffer);
        // auto name = string(buffer);
        // debuglog << "Name: " << name << endl;
        // fscanf(fileHandle, "%s,", buffer);
        // auto textureName = string(buffer);
        // debuglog << "Texture Name: " << textureName << endl;
        // resourceManager->loadTextures({textureName});
        // modelTexture = resourceManager->getTexture(textureName);
        // int vertexCount;
        // fscanf(fileHandle, "%d\n", &vertexCount);
        // debuglog << "Number of vertices: " << vertexCount << endl;
        // int vertexElements;
        // fscanf(fileHandle, "%d\n", &vertexElements);
        // debuglog << "Elements in vertex: " << vertexElements << endl;
        while (!feof(fileHandle))
        {
            fscanf(fileHandle, "%s ", buffer);
            auto instruction = string(buffer);
            if(instruction == "#")
                continue;
            else if(instruction == "")
                continue;
            else if(instruction == "v")
            {
                debuglog << "Reading vertice!" << std::endl;
                float x, y, z;
                fscanf(fileHandle, "%f ", &x);
                fscanf(fileHandle, "%f ", &y);
                fscanf(fileHandle, "%f ", &z);
                verts.emplace_back(Vector3{x,y,z});
            }
            else if(instruction == "vt")
            {
                debuglog << "Reading texture coordinate!" << std::endl;
                float u, v;
                fscanf(fileHandle, "%f ", &u);
                fscanf(fileHandle, "%f ", &v);
                uvs.emplace_back(Vector2{u,v});
            }
            else if(instruction == "vn")
            {
                debuglog << "Reading vertex normal!" << std::endl;
                float x, y, z;
                fscanf(fileHandle, "%f ", &x);
                fscanf(fileHandle, "%f ", &y);
                fscanf(fileHandle, "%f ", &z);
                normals.emplace_back(Vector3{x,y,z});
            }
            else if(instruction == "f")
            {
                debuglog << "Reading face!" << std::endl;
                int v, u, n;
                for (int i = 0; i < 3; i++)
                {
                    fscanf(fileHandle, "%i/", &v);
                    fscanf(fileHandle, "%i/", &u);
                    fscanf(fileHandle, "%i ", &n);
                    vertices.emplace_back(verts[v-1], normals[n-1], uvs[u-1]);
                }                
            }
            else if(instruction == "mtllib")
            {
                debuglog << "Reading material!" << std::endl;
                fscanf(fileHandle, "%s", buffer);
                auto textureName = string("coderox.png");
                debuglog << "Texture Name: " << textureName << endl;
                resourceManager->loadTextures({textureName});
                modelTexture = resourceManager->getTexture(textureName);
            }
            // std::vector<float> value(vertexElements);
            // for (int i = 0; i < vertexElements; i++)
            // {
            //     fscanf(fileHandle, "%f,", &value[i]);
            // }Vector3
            // vertices.emplace_back(
            //     Vector3{value[0], value[1], value[2]},
            //     Vector3{value[3], value[4], value[5]},
            //     Vector2{value[6], value[7]});
        }
    }
    return make_shared<Model>(vertices, modelTexture);
}
