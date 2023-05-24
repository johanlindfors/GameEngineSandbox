#include "resources/ModelLoader.h"
#include "resources/IResourceManager.h"
#include "resources/Model.h"
#include "utilities/IOC.hpp"
#include "filesystem/IFileSystem.h"
#include "File.h"
#include <vector>

using namespace std;
using namespace Engine;
using namespace Utilities;

shared_ptr<Model> ModelLoader::loadModel(const std::string& fileName)
{
    // auto result = make_shared<Model>(nullptr, nullptr);
    // return result;
    auto fileSystem = IOCContainer::instance().resolve<IFileSystem>();
    auto resourceManager = IOCContainer::instance().resolve<IResourceManager>();	
    std::vector<VertexPositionNormalTexture> vertices;
    const auto file = fileSystem->loadFile(std::string("models/" + fileName), false);
    Texture2D modelTexture;
    printf("[ModelLoader::loadModel] Loading model\n");
    if(file && file->isOpen()){
        auto fileHandle = file->get();
        char buffer[100];
        // read header
        fscanf(fileHandle, "%s,", buffer);
        auto name = string(buffer);
        printf("Name: %s\n", name.c_str());
        fscanf(fileHandle, "%s,", buffer);
        auto textureName = string(buffer);
        printf("Texture Name: %s\n", textureName.c_str());
        resourceManager->loadTextures({textureName});
        modelTexture = resourceManager->getTexture(textureName);
        int vertexCount;
        fscanf(fileHandle, "%d\n", &vertexCount);
        printf("Number of vertices: %d\n", vertexCount);
        int vertexElements;
        fscanf(fileHandle, "%d\n", &vertexElements);
        printf("Elements in vertex: %d\n", vertexElements);
        while(!feof(fileHandle)) {
            std::vector<float> value(vertexElements);
            for( int i = 0 ; i < vertexElements; i++ ) {
                fscanf(fileHandle, "%f,", &value[i]);
            }
            vertices.emplace_back(
                Vector3{value[0], value[1], value[2]},
                Vector3{value[3], value[4], value[5]},
                Vector2{value[6], value[7]}
            );
        }
    }
    return make_shared<Model>(vertices, modelTexture);
}