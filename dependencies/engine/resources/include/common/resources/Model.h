#pragma once

#include <vector>
#include "utilities/MathHelper.h"
#include "Texture2D.h"

namespace Engine {
class Model {
public:
    inline Model(
            std::vector<Utilities::Vertex> vertices,
            std::vector<Utilities::Index> indices,
            std::shared_ptr<Engine::Texture2D> spTexture)
            : mVertices(std::move(vertices))
            , mIndices(std::move(indices))
            , mTexture(std::move(spTexture)) {}

    inline const Utilities::Vertex *getVertexData() const {
        return mVertices.data();
    }

    inline const size_t getIndexCount() const {
        return mIndices.size();
    }

    inline const Utilities::Index *getIndexData() const {
        return mIndices.data();
    }

    inline const Engine::Texture2D &getTexture() const {
        return *mTexture;
    }

private:
    std::vector<Utilities::Vertex> mVertices;
    std::vector<Utilities::Index> mIndices;
    std::shared_ptr<Engine::Texture2D> mTexture;
};
}
