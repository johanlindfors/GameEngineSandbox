#include "resources/Model.hpp"

void Engine::ModelBase::initializeGlBuffers()
{
    GlGenVertexArrays(1, &mVAO);
    GlGenBuffers(1, &mVBO);

    GlBindBuffer(GL_ARRAY_BUFFER, mVBO);
}
