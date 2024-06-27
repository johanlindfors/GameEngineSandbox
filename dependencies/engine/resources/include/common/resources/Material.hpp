#pragma once

#include <vector>
#include <string>
#include "Texture2D.hpp"

namespace Engine {

struct Texture2D;

class Material {
public:
    Material();

    inline const Engine::Texture2D getTexture() const
    {
        return mTexture;
    }

    inline void setTexture(Engine::Texture2D texture) {
        mTexture = texture;
    }

    inline void setName(std::string name)
    {
        mName = name;
    }

private:
    std::string mName;
    Engine::Texture2D mTexture;
};

}
