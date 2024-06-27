#include "resources/MaterialLoader.hpp"
#include "resources/IResourceManager.hpp"
#include "resources/Material.hpp"
#include "utilities/IOC.hpp"
#include "utilities/Logger.hpp"
#include "filesystem/IFileSystem.hpp"
#include "filesystem/File.hpp"
#include <memory>

using namespace std;
using namespace Engine;
using namespace Utilities;

shared_ptr<Material> MaterialLoader::loadMaterial(const std::string &fileName)
{
    auto fileSystem = IOCContainer::instance().resolve<IFileSystem>();
    auto resourceManager = IOCContainer::instance().resolve<IResourceManager>();
    const auto file = fileSystem->loadFile(std::string("models/" + fileName), false);
    Texture2D modelTexture;
    std::shared_ptr<Material> material = make_shared<Material>();
    debuglog << "[MaterialLoader::loadMaterial] Loading material" << endl;
    if (file && file->isOpen())
    {
        auto fileHandle = file->get();
        char buffer[100];

        while (!feof(fileHandle))
        {
            fscanf(fileHandle, "%s ", buffer);
            auto instruction = string(buffer);
            if(instruction == "#")
                continue;
            else if(instruction == "")
                continue;
            else if(instruction == "newmtl")
            {
                debuglog << "Reading name!" << std::endl;
                fscanf(fileHandle, "%s ", buffer);
                material->setName(string(buffer));
            }
            else if(instruction == "map_Kd")
            {
                debuglog << "Reading texture name!" << std::endl;
                fscanf(fileHandle, "%s", buffer);
                auto textureFilename = string(buffer);
                resourceManager->loadTextures({textureFilename});
                material->setTexture(resourceManager->getTexture(textureFilename));
            }
            else if(instruction == "Kd") // diffuse color
            {
                // TODO
            }
            else if(instruction == "Ka") // ambient color
            {
                // TODO
            }
            else if(instruction == "Ks") // specular color
            {
                // TODO
            }
            else if(instruction == "Ns") // specular exponent
            {
                // TODO
            }
            else if(instruction == "d") // dissolve
            {
                // TODO
            }
            else if(instruction == "Tr") // transparency (Tr = 1 -d)
            {
                // TODO
            }
            else if(instruction == "Ni") // index of refraction
            {
                // TODO
            }

        }
    }
    return material;
}
