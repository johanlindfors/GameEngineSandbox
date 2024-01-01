#pragma once

#include <vector>
#include "Texture2D.hpp"

namespace Engine {
    union VertexPositionNormalTexture;

    class Model {
    public:
        Model(
            std::vector<Engine::VertexPositionNormalTexture> vertices,
            Engine::Texture2D texture
        );

            Model(
                float vertices[],
                int vertexCount,
                Engine::Texture2D texture);

            inline const size_t getVertexCount() const
            {
                return mVertexCount;
            }

            inline const Engine::Texture2D getTexture() const
            {
                return mTexture;
            }

        inline const unsigned int getVAO() const {
            return mVAO;
        }

    private:
        void InitializeGlBuffers();
        void UpdateGlAttributes();
        unsigned int mVBO;
        unsigned int mVAO;
        Engine::Texture2D mTexture;
        int mVertexCount;
    };
}
