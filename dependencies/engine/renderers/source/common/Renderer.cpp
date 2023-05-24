#include "renderers/Renderer.h"
#include <string>
#include "utilities/GLHelper.h"
#include "renderers/Sprite.h"
#include "renderers/Camera.hpp"
#include "resources/Shader.h"

using namespace std;
using namespace Engine;
using namespace Utilities;

Renderer::Renderer(
    shared_ptr<Shader> shader) 
    : mShader(shader) { } 

Renderer::~Renderer()
{
    printf("[Renderer::~Renderer]\n");
	mShader.reset();
}

void Renderer::initialize()
{
    printf("[Renderer::initialize]\n");
}

void Renderer::updateWindowSize(int width, int height)
{
	printf("[Renderer::updateWindowSize]\n");
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
