#include "renderers/SimpleRenderer.h"
#include "utilities/IOC.hpp"
#include "resources/IResourceManager.h"
#include "resources/Shader.h"
#include "glwrapper.h"

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace Engine;
using namespace Utilities;

void SimpleRenderer::initialize() 
{
    printf("[SimpleRenderer::initialize] In initialize\n");
    auto resourceManager = IOCContainer::instance().resolve<IResourceManager>();
    resourceManager->loadShader("basic_lighting", "basic_lighting.vs", "basic_lighting.fs");
	resourceManager->loadShader("light_cube", "light_cube.vs", "light_cube.fs");

    lightingShader = resourceManager->getShader("basic_lighting");
    lightCubeShader = resourceManager->getShader("light_cube");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };
    // first, configure the cube's VAO (and VBO)
    GlGenVertexArrays(1, &cubeVAO);
    GlGenBuffers(1, &VBO);

    GlBindBuffer(GL_ARRAY_BUFFER, VBO);
    GlBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GlBindVertexArray(cubeVAO);

    // position attribute
    GlVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    GlEnableVertexAttribArray(0);
    // normal attribute
    GlVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    GlEnableVertexAttribArray(1);


    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    GlGenVertexArrays(1, &lightCubeVAO);
    GlBindVertexArray(lightCubeVAO);

    GlBindBuffer(GL_ARRAY_BUFFER, VBO);
    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    GlVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    GlEnableVertexAttribArray(0);

    GlEnable(GL_DEPTH_TEST);
    // glEnable(GL_CULL_FACE);
    // glCullFace(GL_BACK);
    // glFrontFace(GL_CW); 
}

void SimpleRenderer::updateWindowSize(int width, int height) { }

void SimpleRenderer::draw()
{
    // lighting
    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

    lightingShader->use();
    lightingShader->setVector3f("objectColor", 1.0f, 0.5f, 0.31f);
    lightingShader->setVector3f("lightColor", 1.0f, 1.0f, 1.0f);
    lightingShader->setVector3f("lightPos", lightPos.x, lightPos.y, lightPos.z);

    // view/projection transformations
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)800 / (float)600, 0.1f, 100.0f);
    glm::mat4 view = camera.getViewMatrix();
    lightingShader->setMatrix4("projection", projection);
    lightingShader->setMatrix4("view", view);

    // world transformation
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, angle += 0.01f, glm::vec3(1.0f,1.0f,1.0f));
    lightingShader->setMatrix4("model", model);

    // render the cube
    GlBindVertexArray(cubeVAO);
    GlDrawArrays(GL_TRIANGLES, 0, 36);


    // also draw the lamp object
    lightCubeShader->use();
    lightCubeShader->setMatrix4("projection", projection);
    lightCubeShader->setMatrix4("view", view);
    model = glm::mat4(1.0f);
    model = glm::translate(model, lightPos);
    model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
    lightCubeShader->setMatrix4("model", model);

    GlBindVertexArray(lightCubeVAO);
    GlDrawArrays(GL_TRIANGLES, 0, 36);
}

void SimpleRenderer::clear()
{
    GlClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    GlClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
