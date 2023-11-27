#include "renderers/Renderer.hpp"
#include <string>
#include "utilities/GLHelper.hpp"
#include "sprites/Sprite.hpp"
#include "renderers/Camera.hpp"
#include "resources/Shader.hpp"
#include "utilities/Logger.hpp"

using namespace std;
using namespace Engine;

Renderer::Renderer(
    shared_ptr<Shader> shader)
    : mShader(shader) {}

Renderer::~Renderer()
{
    debuglog << "[Renderer::~Renderer]" << endl;
	mShader.reset();
}

void Renderer::initialize()
{
    debuglog << "[Renderer::initialize]" << endl;
}

void Renderer::updateWindowSize(int width, int height)
{
	debuglog << "[Renderer::updateWindowSize]" << endl;
    GlViewport(0, 0, width, height);
}

void Renderer::clear()
{
    clear(0.0f, 0.0f, 0.0f, 1.0f);
}

void Renderer::clear(float r, float g, float b, float a)
{
    GlClearColor(r, g, b, a);
}
