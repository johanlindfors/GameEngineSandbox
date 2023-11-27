#include "renderers/ModelRenderer.hpp"
#include <string>
#include "resources/Model.hpp"
#include "renderers/Camera.hpp"
#include "resources/Shader.hpp"
#include "utilities/Logger.hpp"

using namespace std;
using namespace Engine;
using namespace Utilities;

ModelRenderer::ModelRenderer(
    shared_ptr<Shader> shader,
    shared_ptr<Camera> camera)
    : Renderer::Renderer(shader), mCamera(camera)
{
}

ModelRenderer::~ModelRenderer()
{
    mShader.reset();
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
}

void ModelRenderer::initialize()
{
    debuglog << "[ModelRenderer::initialize]" << endl;
}

void ModelRenderer::updateWindowSize(int width, int height)
{
	debuglog << "[ModelRenderer::updateWindowSize]" << endl;
    GlViewport(0, 0, width, height);
}

void ModelRenderer::clear()
{
    Renderer::clear();
    GlClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    GlEnable(GL_DEPTH_TEST);
}

void ModelRenderer::clear(float r, float g, float b, float a)
{
    Renderer::clear(r, g, b, a);
    GlClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    GlEnable(GL_DEPTH_TEST);
}

void ModelRenderer::drawModel(shared_ptr<Model> model, glm::mat4 &world)
{
    mShader->use();
    checkOpenGLError();

    // lighting
    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

    mShader->setVector3f("objectColor", 0.35f, 0.35f, 0.34f);
    mShader->setVector3f("lightColor", 1.0f, 1.0f, 1.0f);
    mShader->setVector3f("lightPos", lightPos.x, lightPos.y, lightPos.z);

    // view/projection transformations
    mShader->setMatrix4("projection", mCamera->getProjectionMatrix());
    mShader->setMatrix4("view", mCamera->getViewMatrix());

    // world transformation
    mShader->setMatrix4("model", world);
    mShader->setMatrix4("normalRotation", glm::transpose(glm::inverse(world)));

    glBindTexture(GL_TEXTURE_2D, model->getTexture().textureIndex); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    // glFrontFace(GL_CCW);

    // glDisable(GL_DEPTH_TEST);
    // render
    GlBindVertexArray(model->getVAO());
    GlDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(model->getVertexCount()));
    glEnable(GL_DEPTH_TEST);
}
