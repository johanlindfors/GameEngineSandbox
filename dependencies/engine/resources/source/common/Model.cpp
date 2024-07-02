#include "resources/Model.hpp"

void Engine::ModelBase::InitializeGlBuffers()
{
    GlGenVertexArrays(1, &mVAO);
    GlGenBuffers(1, &mVBO);

    GlBindBuffer(GL_ARRAY_BUFFER, mVBO);
}
