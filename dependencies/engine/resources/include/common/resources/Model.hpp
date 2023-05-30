#pragma once

#include <vector>
#include "utilities/MathHelper.hpp"
#include "Texture2D.hpp"

namespace Engine {
class Model {
public:
    Model(
        std::vector<Utilities::VertexPositionNormalTexture> vertices,
        Engine::Texture2D texture
    );

    Model(
        float vertices[],
        int vertexCount,
        Engine::Texture2D texture
    );

    inline const size_t getVertexCount() const {
        return mVertexCount;
    }

    inline const Engine::Texture2D getTexture() const {
        return mTexture;
    }

    unsigned int VAO;

private:
    void InitializeGlBuffers();
    void UpdateGlAttributes();
    unsigned int mVBO;
    Engine::Texture2D mTexture;
    int mVertexCount;
};

class OldModel {
public:
    inline OldModel(
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
