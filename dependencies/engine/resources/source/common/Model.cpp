#include "resources/Model.hpp"
#include <vector>
#include "utilities/MathHelper.hpp"
#include "resources/Material.hpp"
#include "utilities/GLHelper.hpp"

using namespace Engine;
using namespace Utilities;

// Model::Model(
//     std::vector<VertexPositionTexture> vertices,
//     Material material)
//     : mMaterial(material)
//     , mVertexCount(static_cast<int>(vertices.size()))
// {
//     InitializeGlBuffers();

//     GlBufferData(GL_ARRAY_BUFFER, sizeof(VertexPositionTexture) * vertices.size(), static_cast<void *>(&vertices[0]), GL_STATIC_DRAW);

//     UpdateGlAttributes();
// }

Model::Model(
    float vertices[],
    int vertexCount,
    Material material)
    : mMaterial(material)
    , mVertexCount(vertexCount)
{
    InitializeGlBuffers();

    GlBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexCount, static_cast<void *>(vertices), GL_STATIC_DRAW);

    UpdateGlAttributes();
}

void Model::InitializeGlBuffers()
{
    GlGenVertexArrays(1, &mVAO);
    GlGenBuffers(1, &mVBO);

    GlBindBuffer(GL_ARRAY_BUFFER, mVBO);
}

void Model::UpdateGlAttributes()
{
    GlBindVertexArray(mVAO);

    // position attribute
    GlVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    GlEnableVertexAttribArray(0);
    // // normal attribute
    // GlVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void *>(3 * sizeof(float)));
    // GlEnableVertexAttribArray(1);
    // texture coordinate attribute
    GlVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void *>(3 * sizeof(float)));
    GlEnableVertexAttribArray(1);
}
