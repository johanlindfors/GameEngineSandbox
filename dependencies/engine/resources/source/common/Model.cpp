#include "resources/Model.h"
#include <vector>
#include "utilities/MathHelper.h"
#include "resources/Texture2D.h"
#include "utilities/GLHelper.h"

using namespace Engine;
using namespace Utilities;

Model::Model(
    std::vector<VertexPositionNormalTexture> vertices,
    Texture2D texture)
    : mTexture(texture)
    , mVertexCount(static_cast<int>(vertices.size())) 
{ 
    InitializeGlBuffers();
    
    GlBufferData(GL_ARRAY_BUFFER, sizeof(VertexPositionNormalTexture) * vertices.size(), static_cast<void*>(&vertices[0]), GL_STATIC_DRAW);

    UpdateGlAttributes();
}

Model::Model(
    float vertices[],
    int vertexCount,
    Texture2D texture)
    : mTexture(texture)
    , mVertexCount(vertexCount) 
{
    InitializeGlBuffers();

    GlBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexCount, static_cast<void*>(vertices), GL_STATIC_DRAW);

    UpdateGlAttributes();
}

void Model::InitializeGlBuffers()
{
    GlGenVertexArrays(1, &VAO);
    GlGenBuffers(1, &mVBO);

    GlBindBuffer(GL_ARRAY_BUFFER, mVBO);
}

void Model::UpdateGlAttributes()
{
    GlBindVertexArray(VAO);

    // position attribute
    GlVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    GlEnableVertexAttribArray(0);
    // normal attribute
    GlVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
    GlEnableVertexAttribArray(1);
    // texture coordinate attribute
    GlVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(6 * sizeof(float)));
    GlEnableVertexAttribArray(2);
}
