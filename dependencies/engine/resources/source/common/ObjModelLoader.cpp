#include "resources/ObjModelLoader.hpp"
#include "resources/IResourceManager.hpp"
#include "resources/Model.hpp"
#include "utilities/MathHelper.hpp"
#include "utilities/IOC.hpp"
#include "utilities/Logger.hpp"
#include "filesystem/IFileSystem.hpp"
#include "filesystem/File.hpp"
#include "resources/Material.hpp"
#include <vector>

using namespace std;
using namespace Engine;
using namespace Utilities;

// template<class T>
// shared_ptr<T> ObjModelLoader::loadModel(const std::string &fileName)
// {
//     auto fileSystem = IOCContainer::instance().resolve<IFileSystem>();
//     auto resourceManager = IOCContainer::instance().resolve<IResourceManager>();
//     std::vector<Vector3> verts;
//     //std::vector<Vector3> normals;
//     std::vector<Vector2> uvs;
//     std::vector<VertexPositionTexture> vertices;
//     const auto file = fileSystem->loadFile(std::string("models/" + fileName), false);
//     Material material;
//     debuglog << "[ModelLoader::loadModel] Loading model" << endl;
//     if (file && file->isOpen())
//     {
//         auto fileHandle = file->get();
//         char buffer[100];

//         while (!feof(fileHandle))
//         {
//             fscanf(fileHandle, "%s ", buffer);
//             auto instruction = string(buffer);
//             if(instruction == "#")
//                 continue;
//             else if(instruction == "")
//                 continue;
//             else if(instruction == "v")
//             {
//                 const int MAX_VERTICES = 9;
//                 float vertex[MAX_VERTICES];
//                 int i = 0;
//                 while(i < MAX_VERTICES && fscanf(fileHandle, "%f ", &vertex[i]) > 0) {
//                     i++;
//                 }
//                 if(i >=3)
//                     verts.emplace_back(Vector3{vertex[0],vertex[1],vertex[2]});
//                 if(i >=4)
//                     throw;
//                 debuglog << "Read vertex!" << vertex[0] << "," << vertex[1] << "," << vertex[2] << std::endl;
//             }
//             else if(instruction == "vt")
//             {
//                 debuglog << "Reading texture coordinate!" << std::endl;
//                 float u, v;
//                 fscanf(fileHandle, "%f %f", &u, &v);
//                 uvs.emplace_back(Vector2{u,v});
//             }
//             else if(instruction == "vn")
//             {
//                 debuglog << "Reading vertex normal!" << std::endl;
//                 float x, y, z;
//                 fscanf(fileHandle, "%f ", &x);
//                 fscanf(fileHandle, "%f ", &y);
//                 fscanf(fileHandle, "%f ", &z);
//                 //normals.emplace_back(Vector3{x,y,z});
//             }
//             else if(instruction == "f")
//             {
//                 //debuglog << "Reading face!" << std::endl;
//                 const int MAX_FACES = 4;
//                 int v[MAX_FACES], u[MAX_FACES];
//                 int i = 0;
//                 while(i < MAX_FACES && fscanf(fileHandle, "%i/%i ", &v[i], &u[i]) > 0)
//                     i++;
//                 if(i >= 3) {
//                     vertices.emplace_back(verts[v[0]-1], uvs[u[0]-1]);
//                     vertices.emplace_back(verts[v[1]-1], uvs[u[1]-1]);
//                     vertices.emplace_back(verts[v[2]-1], uvs[u[2]-1]);
//                 }
//                 if(i == 4) {
//                     vertices.emplace_back(verts[v[0]-1], uvs[u[0]-1]);
//                     vertices.emplace_back(verts[v[2]-1], uvs[u[2]-1]);
//                     vertices.emplace_back(verts[v[3]-1], uvs[u[3]-1]);
//                 }
//             }
//             else if(instruction == "mtllib")
//             {
//                 debuglog << "Reading material!" << std::endl;
//                 fscanf(fileHandle, "%s", buffer);
//                 auto materialFilename = string(buffer);
//                 resourceManager->loadMaterial(materialFilename);
//                 // debuglog << "Texture Name: " << textureName << endl;
//                 // resourceManager->loadTextures({textureName});
//                 material = resourceManager->getMaterial(materialFilename);
//             }
//         }
//     }
//     return make_shared<T>(vertices, material);
// }
