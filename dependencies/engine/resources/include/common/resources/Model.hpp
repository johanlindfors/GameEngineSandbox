#pragma once

#include <vector>
#include "Material.hpp"
#include "utilities/MathHelper.hpp"
#include "utilities/glwrapper.hpp"

namespace Engine {

class ModelBase
{
public:
    ModelBase(Material material) 
    : mMaterial(material) { }

    inline const size_t getVertexCount() const { return mVertexCount; }
    inline const Engine::Material getMaterial() const { return mMaterial; }
    inline const unsigned int getVAO() const { return mVAO; }

protected:
    unsigned int mVBO;
    unsigned int mVAO;
    Material mMaterial;
    int mVertexCount;
};

template <class T>
class Model : public ModelBase
{

protected:
    void InitializeGlBuffers();
    void UpdateGlAttributes();
};

template <>
class Model <Utilities::VertexPosition> : public ModelBase
{
    Model(
        std::vector<Utilities::VertexPosition> vertices,
        Engine::Material material
    ) : ModelBase(material) {
        InitializeGlBuffers();

        GlBufferData(GL_ARRAY_BUFFER, sizeof(VertexPosition) * vertices.size(), static_cast<void *>(&vertices[0]), GL_STATIC_DRAW);

        UpdateGlAttributes();
    }
};

template <>
class Model <Utilities::VertexPositionTexture> : public ModelBase
{
    Model(
        std::vector<Utilities::VertexPositionTexture> vertices,
        Engine::Material material
    ) : ModelBase(material) {
        
    }
};
// class Model {
// public:
//     Model(
//         std::vector<Utilities::VertexPositionTexture> vertices,
//         Engine::Material material
//     );

//     Model(
//         float vertices[],
//         int vertexCount,
//         Engine::Material material
//     );

//     inline const size_t getVertexCount() const
//     {
//         return mVertexCount;
//     }

//     inline const Engine::Material getMaterial() const
//     {
//         return mMaterial;
//     }

//     inline const unsigned int getVAO() const {
//         return mVAO;
//     }

// private:
//     void InitializeGlBuffers();
//     void UpdateGlAttributes();
//     unsigned int mVBO;
//     unsigned int mVAO;
//     Material mMaterial;
//     int mVertexCount;
// };

}
