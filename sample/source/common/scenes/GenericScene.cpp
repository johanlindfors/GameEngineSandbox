#include "GenericScene.h"
#include "utilities/IOC.hpp"
#include "resources/IResourceManager.h"
#include "utilities/MathHelper.h"
#include "filesystem/FileSystem.h"
#include "File.h"

using namespace std;
using namespace Engine;
using namespace Utilities;
using namespace Sample;

//! Color for cornflower blue. Can be sent directly to glClearColor
#define CORNFLOWER_BLUE 100 / 255.f, 149 / 255.f, 237 / 255.f, 1

static constexpr float kProjectionHalfHeight = 2.f;
static constexpr float kProjectionNearPlane = -1.f;
static constexpr float kProjectionFarPlane = 1.f;

void GenericScene::load() 
{
    printf("[GenericScene::load]\n");
    auto resourceManager = IOCContainer::instance().resolve<IResourceManager>();
    auto fileSystem = IOCContainer::instance().resolve<IFileSystem>();
     /*
     * This is a square:
     * 0 --- 1
     * | \   |
     * |  \  |
     * |   \ |
     * 3 --- 2
     */
    std::vector<Vertex> vertices = {
        Vertex(Vector3{1, 1, 0}, Vector2{0, 0}),    // 0
        Vertex(Vector3{-1, 1, 0}, Vector2{1, 0}),   // 1
        Vertex(Vector3{-1, -1, 0}, Vector2{1, 1}),  // 2
        Vertex(Vector3{1, -1, 0}, Vector2{0, 1})    // 3
    };
    std::vector<Index> indices = {
            0, 1, 2, 0, 2, 3
    };

    resourceManager->loadTextures({ "coderox.png" });
    auto spTexture = make_shared<Texture2D>(resourceManager->getTexture( "coderox.png" ));
    
    // Create a model and put it in the back of the render list.
    mModels.emplace_back(vertices, indices, spTexture);

    auto vsFile = fileSystem->loadFile("shaders/simple.vs", false);
    auto fsFile = fileSystem->loadFile("shaders/simple.fs", false);

    auto vs = vsFile->readAllText();
    auto fs = fsFile->readAllText();

    mShader = std::unique_ptr<GenericShader>(
            GenericShader::loadShader(vs, fs, 0, 1, 0)); // hardcoded values
    if(mShader.get()){
        printf("Here\n");
        mShader->activate();
    }

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
