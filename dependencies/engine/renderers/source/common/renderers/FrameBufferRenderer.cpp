#include "renderers/FrameBufferRenderer.hpp"
#include "utilities/glwrapper.hpp"
#include "utilities/Config.hpp"
#include "utilities/Logger.hpp"
#include "resources/Shader.hpp"

using namespace std;
using namespace Engine;
using namespace Utilities;

FrameBufferRenderer::FrameBufferRenderer()
{

}

FrameBufferRenderer::~FrameBufferRenderer()
{
    GlDeleteVertexArrays(1, &quadVAO);
    GlDeleteBuffers(1, &quadVBO);
    GlDeleteRenderbuffers(1, &rbo);
    GlDeleteFramebuffers(1, &framebuffer);
}

void FrameBufferRenderer::initialize(shared_ptr<Config> config, shared_ptr<Shader> shader)
{
    mShader = shader;

    float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
        // positions   // texCoords
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };

    mWidth = config->width;
    mHeight = config->height;

    // screen quad VAO
    GlGenVertexArrays(1, &quadVAO);
    GlGenBuffers(1, &quadVBO);
    GlBindVertexArray(quadVAO);
    GlBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    GlBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    GlEnableVertexAttribArray(0);
    GlVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    GlEnableVertexAttribArray(1);
    GlVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    // framebuffer configuration
    // -------------------------
    GlGenFramebuffers(1, &framebuffer);
    GlBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

    // create a color attachment texture
    GlGenTextures(1, &textureColorbuffer);
    GlBindTexture(GL_TEXTURE_2D, textureColorbuffer);
    GlTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mWidth, mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    GlTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    GlTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    GlFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);

    // create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
    GlGenRenderbuffers(1, &rbo);
    GlBindRenderbuffer(GL_RENDERBUFFER, rbo);
    GlRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, mWidth, mHeight); // use a single renderbuffer object for both a depth AND stencil buffer.
    GlFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it
    // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
    if (GlCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        debuglog << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;
    GlBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBufferRenderer::updateScreenSize(int width, int height)
{
    mScreenWidth = width;
    mScreenHeight = height;

    debuglog << "Game Size: " << mWidth << "x" << mHeight << " Screen Size: " << mScreenWidth << "x" << mScreenHeight << endl;
}

void FrameBufferRenderer::begin()
{
    GlBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    GlViewport(0,0, mWidth, mHeight);
}

void FrameBufferRenderer::end()
{
    // now bind back to default framebuffer and draw a quad plane with the attached framebuffer color texture
    GlBindFramebuffer(GL_FRAMEBUFFER, 0);
    GlViewport(0,0,mScreenWidth, mScreenHeight);
    GlDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
    // clear all relevant buffers
    GlClear(GL_COLOR_BUFFER_BIT);

    mShader->use();
    GlBindVertexArray(quadVAO);
    GlBindTexture(GL_TEXTURE_2D, textureColorbuffer);	// use the color attachment texture as the texture of the quad plane
    GlDrawArrays(GL_TRIANGLES, 0, 6);
}
