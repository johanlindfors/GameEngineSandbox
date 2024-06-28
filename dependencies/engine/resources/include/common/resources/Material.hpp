#pragma once

#include <vector>
#include <string>
#include "Texture2D.hpp"
#include "utilities/MathHelper.hpp"

namespace Engine {

struct Material {
    std::string Name;
    Engine::Texture2D Texture;
    Utilities::Vector3 Diffuse;
};

}
