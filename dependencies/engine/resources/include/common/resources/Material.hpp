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
    Utilities::Vector3 Ambient;
    Utilities::Vector3 Specular;
    float SpecularExponent;
};

}
