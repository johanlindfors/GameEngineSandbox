#pragma once

#include <vector>
#include "Material.hpp"

namespace Utilities {
    union VertexPositionTexture;
}

namespace Engine {

class Model {
public:
    Model(
        std::vector<Utilities::VertexPositionTexture> vertices,
        Engine::Material material
    );

    Model(
        float vertices[],
        int vertexCount,
        Engine::Material material
    );

    inline const size_t getVertexCount() const
    {
        return mVertexCount;
    }

    inline const Engine::Material getMaterial() const
    {
        return mMaterial;
    }

    inline const unsigned int getVAO() const {
        return mVAO;
    }

private:
    void InitializeGlBuffers();
    void UpdateGlAttributes();
    unsigned int mVBO;
    unsigned int mVAO;
    Material mMaterial;
    int mVertexCount;
};

}
