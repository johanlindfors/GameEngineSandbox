#include "GenericScene.h"
#include "utilities/IOC.hpp"
#include "resources/IResourceManager.h"
#include "utilities/MathHelper.h"

using namespace std;
using namespace Engine;
using namespace Utilities;
using namespace Sample;

// Vertex shader, you'd typically load this from assets
static const char *vertex = R"vertex(#version 300 es
in vec3 inPosition;
in vec2 inUV;

out vec2 fragUV;

uniform mat4 uMVP;

void main() {
    fragUV = inUV;
    gl_Position = uMVP * vec4(inPosition, 1.0);
}
)vertex";

// Fragment shader, you'd typically load this from assets
static const char *fragment = R"fragment(#version 300 es
precision mediump float;

in vec2 fragUV;

uniform sampler2D uTexture;

out vec4 outColor;

void main() {
    outColor = texture(uTexture, fragUV);
}
)fragment";

//! Color for cornflower blue. Can be sent directly to glClearColor
#define CORNFLOWER_BLUE 100 / 255.f, 149 / 255.f, 237 / 255.f, 1

static constexpr float kProjectionHalfHeight = 2.f;
static constexpr float kProjectionNearPlane = -1.f;
static constexpr float kProjectionFarPlane = 1.f;

void GenericScene::load() 
{
    printf("[GenericScene::load]\n");
    auto resourceManager = IOCContainer::instance().resolve<IResourceManager>();

     /*
     * This is a square:
     * 0 --- 1
     * | \   |
     * |  \  |
     * |   \ |
     * 3 --- 2
     */
    std::vector<Vertex> vertices = {
            Vertex(Vector3{1, 1, 0}, Vector2{0, 0}), // 0
            Vertex(Vector3{-1, 1, 0}, Vector2{1, 0}), // 1
            Vertex(Vector3{-1, -1, 0}, Vector2{1, 1}), // 2
            Vertex(Vector3{1, -1, 0}, Vector2{0, 1}) // 3
    };
    std::vector<Index> indices = {
            0, 1, 2, 0, 2, 3
    };

    resourceManager->loadTextures({ "coderox.png"});
    auto spTexture = make_shared<Texture2D>(resourceManager->getTexture("coderox.png"));
    
    // Create a model and put it in the back of the render list.
    mModels.emplace_back(vertices, indices, spTexture);

    mShader = std::unique_ptr<GenericShader>(
            GenericShader::loadShader(vertex, fragment, "inPosition", "inUV", "uMVP"));
    mShader->activate();

    // setup any other gl related global states
    glClearColor(CORNFLOWER_BLUE);

    // enable alpha globally for now, you probably don't want to do this in a game
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void GenericScene::unload() 
{
    printf("[GenericScene::Unload]\n");
    mShader->deactivate();
}

void GenericScene::updateScreenSize(int width, int height)
{ 
    printf("[GenericScene::UpdateScreenSize]\n");
    mWidth = width;
    mHeight = height;
}

void GenericScene::update(shared_ptr<IStepTimer> timer)
{
    // printf("[GenericScene::Update]\n");
}

void GenericScene::draw(std::shared_ptr<Engine::IRenderer> renderer)
{
    // printf("[GenericScene::Draw]\n");
    float mvpMatrix[16] = {0};
    buildOrthographicMatrix(
                mvpMatrix,
                -kProjectionHalfHeight,
                float(mWidth)/mHeight,
                kProjectionNearPlane,
                kProjectionFarPlane);

    mShader->setMvpMatrix(mvpMatrix);

    glClear(GL_COLOR_BUFFER_BIT);

    if (!mModels.empty()) {
        for (const auto &model: mModels) {
            mShader->drawModel(model);
        }
    }
}
