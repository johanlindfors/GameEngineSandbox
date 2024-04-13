#include "resources/ModelLoader.hpp"
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

shared_ptr<Model> ModelLoader::loadModel(const std::string &fileName)
{
    auto fileSystem = IOCContainer::instance().resolve<IFileSystem>();
    auto resourceManager = IOCContainer::instance().resolve<IResourceManager>();
    std::vector<VertexPositionNormalTexture> vertices;
    const auto file = fileSystem->loadFile(std::string("models/" + fileName), false);
    Texture2D modelTexture;
    debuglog << "[ModelLoader::loadModel] Loading model" << endl;
    if (file && file->isOpen())
    {
        auto fileHandle = file->get();
        char buffer[100];
        // read header
        fscanf(fileHandle, "%s,", buffer);
        auto name = string(buffer);
        debuglog << "Name: " << name << endl;
        fscanf(fileHandle, "%s,", buffer);
        auto textureName = string(buffer);
        debuglog << "Texture Name: " << textureName << endl;
        resourceManager->loadTextures({textureName});
        modelTexture = resourceManager->getTexture(textureName);
        int vertexCount;
        fscanf(fileHandle, "%d\n", &vertexCount);
        debuglog << "Number of vertices: " << vertexCount << endl;
        int vertexElements;
        fscanf(fileHandle, "%d\n", &vertexElements);
        debuglog << "Elements in vertex: " << vertexElements << endl;
        while (!feof(fileHandle))
        {
            std::vector<float> value(vertexElements);
            for (int i = 0; i < vertexElements; i++)
            {
                fscanf(fileHandle, "%f,", &value[i]);
            }
            vertices.emplace_back(
                Vector3{value[0], value[1], value[2]},
                Vector3{value[3], value[4], value[5]},
                Vector2{value[6], value[7]});
        }
    }
    return make_shared<Model>(vertices, modelTexture);
}
