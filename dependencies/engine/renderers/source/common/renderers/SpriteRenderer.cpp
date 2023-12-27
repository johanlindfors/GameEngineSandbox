#include "renderers/SpriteRenderer.hpp"
#include <string>
#include "utilities/GLHelper.hpp"
#include "sprites/Sprite.hpp"
#include "renderers/Camera.hpp"
#include "resources/Shader.hpp"
#include "utilities/Logger.hpp"

using namespace std;
using namespace Engine;
using namespace Utilities;

SpriteRenderer::SpriteRenderer(
    shared_ptr<Shader> shader,
    shared_ptr<OrthographicCamera> camera)
    : Renderer::Renderer(shader), mCamera(camera), mEBO(0), mVAO(0), mVBO(0)
{
}

SpriteRenderer::~SpriteRenderer()
{
    mShader.reset();
}

void SpriteRenderer::initialize()
{
    Renderer::initialize();
    debuglog << "[SpriteRenderer::initialize]" << endl;

    float vertices[] = {
        // pos      // tex
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 1.0f};

    unsigned int indices[] = {
        0, 3, 1, // first triangle
        1, 3, 2  // second triangle
    };
    GlGenVertexArrays(1, &mVAO);
    GlGenBuffers(1, &mVBO);
    GlGenBuffers(1, &mEBO);

    GlBindVertexArray(mVAO);

    GlBindBuffer(GL_ARRAY_BUFFER, mVBO);
    GlBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GlBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
    GlBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    auto attribLocation = mShader->getAttribLocation("vertex");
    GlVertexAttribPointer(attribLocation, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
    GlEnableVertexAttribArray(0);
}

void SpriteRenderer::updateWindowSize(int width, int height)
{
    Renderer::updateWindowSize(width, height);
    mCamera->right = static_cast<float>(width);
    mCamera->top = static_cast<float>(height);
    GlViewport(0, 0, static_cast<GLint>(width), static_cast<GLint>(height));
}

void SpriteRenderer::clear(float r, float g, float b, float a)
{
    Renderer::clear(r, g, b, a);
    GlDisable(GL_DEPTH_TEST);
    GlClear(GL_COLOR_BUFFER_BIT);
}

void SpriteRenderer::drawSprite(shared_ptr<Sprite> sprite)
{
    drawSprite(sprite, sprite->position);
}

void SpriteRenderer::drawSprite(shared_ptr<Sprite> sprite, Point<float> position)
{
    mShader->use();

    glm::mat4 world = glm::mat4(1.0f);
    world = glm::translate(world, glm::vec3(position.x, position.y, 0.0f));
    if (sprite->rotation != 0.0f)
    {
        world = glm::translate(world, glm::vec3(0.5f * sprite->texture.width, 0.5f * sprite->texture.height, 0.0f));
        world = glm::rotate(world, glm::radians(sprite->rotation), glm::vec3(0.0f, 0.0f, 1.0f));
        world = glm::translate(world, glm::vec3(-0.5f * sprite->texture.width, -0.5f * sprite->texture.height, 0.0f));
    }
    world = glm::scale(world, glm::vec3(sprite->size.width, sprite->size.height, 1.0f));

    GLfloat offset[4] = {
        sprite->offset.position.x,
        sprite->offset.position.y,
        (sprite->offset.size.width),
        (sprite->offset.size.height)};

    mShader->setVector4f("offset", offset[0], offset[1], offset[2], offset[3]);
    mShader->setMatrix4("world", world);
    mShader->setMatrix4("projection", mCamera->getProjectionMatrix());

    GlBindTexture(GL_TEXTURE_2D, sprite->texture.textureIndex); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    GlTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
    GlTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    GlEnable(GL_BLEND);
    GlBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    GlBindVertexArray(mVAO);
    GlDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
