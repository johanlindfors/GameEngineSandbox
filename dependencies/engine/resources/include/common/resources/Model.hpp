#pragma once

#include <vector>
#include "Material.hpp"
#include "utilities/MathHelper.hpp"
#include "utilities/glwrapper.hpp"
#include "utilities/Logger.hpp"

namespace Engine {

class ModelBase
{
public:
    ModelBase(Material material, int vertexCount) 
    : mMaterial(material)
    , mVertexCount(vertexCount) {
        InitializeGlBuffers();
    }

    inline const int getVertexCount() const { return mVertexCount; }
    inline const Engine::Material getMaterial() const { return mMaterial; }
    inline const unsigned int getVAO() const { return mVAO; }

    virtual void UpdateGlAttributes() = 0;

protected:
    void InitializeGlBuffers();

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
public:
    Model(
        std::vector<Utilities::VertexPosition> vertices,
        Engine::Material material
    ) : ModelBase(material, vertices.size()) {
        GlBufferData(GL_ARRAY_BUFFER, sizeof(Utilities::VertexPosition) * vertices.size(), static_cast<void *>(&vertices[0]), GL_STATIC_DRAW);
        UpdateGlAttributes();
    }

    virtual void UpdateGlAttributes() override
    {
        GlBindVertexArray(mVAO);

        // position attribute
        GlVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
        GlEnableVertexAttribArray(0);
    }
};

template <>
class Model <Utilities::VertexPositionTexture> : public ModelBase
{
public:
    Model(
        std::vector<Utilities::VertexPositionTexture> vertices,
        Engine::Material material
    ) : ModelBase(material, vertices.size()) {
        GlBufferData(GL_ARRAY_BUFFER, sizeof(Utilities::VertexPositionTexture) * vertices.size(), static_cast<void *>(&vertices[0]), GL_STATIC_DRAW);
        UpdateGlAttributes();        
    }

    virtual void UpdateGlAttributes() override
    {
        GlBindVertexArray(mVAO);

        // position attribute
        GlVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
        GlEnableVertexAttribArray(0);
        // texture coordinate attribute
        GlVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void *>(6 * sizeof(float)));
        GlEnableVertexAttribArray(2);
    }
};

template <>
class Model <Utilities::VertexPositionNormalTexture> : public ModelBase
{
public:
    Model(
        std::vector<Utilities::VertexPositionNormalTexture> vertices,
        Engine::Material material
    ) : ModelBase(material, vertices.size()) {
        GlBufferData(GL_ARRAY_BUFFER, sizeof(Utilities::VertexPositionNormalTexture) * vertices.size(), static_cast<void *>(&vertices[0]), GL_STATIC_DRAW);
        UpdateGlAttributes();
    }

    virtual void UpdateGlAttributes() override
    {
        GlBindVertexArray(mVAO);
    
        // position attribute
        GlVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
        GlEnableVertexAttribArray(0);
        // normal attribute
        GlVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void *>(3 * sizeof(float)));
        GlEnableVertexAttribArray(1);
        // texture coordinate attribute
        GlVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void *>(6 * sizeof(float)));
        GlEnableVertexAttribArray(2);
    }
};

}
