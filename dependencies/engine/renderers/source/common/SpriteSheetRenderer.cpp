#include "renderers/SpriteSheetRenderer.h"
#include <string>
#include "utilities/MathHelper.h"
#include "utilities/GLHelper.h"
#include "renderers/Sprite.h"
#include "filesystem/IFileSystem.h"
#include "utilities/IOC.hpp"
#include "File.h"
#include "resources/IResourceManager.h"

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/vec2.hpp>
#include <vector>

#define STRING(s) #s
#define BUFFER_OFFSET(i) (reinterpret_cast<void*>(i))

using namespace std;
using namespace Engine;
using namespace Utilities;


SpriteSheetRenderer::SpriteSheetRenderer(string filename)
	: mFilename(filename)
	, mInitialized(false)
	, mUVAttribLocation(0)
	, mVertexAttribLocation(0)
	, mVertexPositionBuffer(0)
	, mVertexUVBuffer(0)
	, mWindowHeight(0)
	, mWindowWidth(0)
{ 
}

void SpriteSheetRenderer::lazyInitialize()
{
	initializeShaders();
	initializeVertexBuffer();
	loadSpriteSheet(mFilename);
}

void SpriteSheetRenderer::initialize() { }

void SpriteSheetRenderer::loadSpriteSheet(string fileName)
{
	auto filesystem = IOCContainer::instance().resolve<IFileSystem>();
	auto file = filesystem->loadFile(fileName, false);
	if(file->isOpen()) {
		int x1, y1, x2, y2;
		char buffer[100];
		auto fileHandle = file->get();
		while(!feof(fileHandle)) {
    	    fscanf(fileHandle, "%d,%d,%d,%d", &x1, &y1, &x2, &y2);
			addUVs(x1, y1, x2, y2);
	        fgets(buffer, 100, fileHandle); // skip the rest of the line
		}
    }
    
	initializeUVBuffer();
}

SpriteSheetRenderer::~SpriteSheetRenderer()
{
	if (mVertexPositionBuffer != 0)
	{
		GlDeleteBuffers(1, &mVertexPositionBuffer);
		mVertexPositionBuffer = 0;
	}

	if (mVertexUVBuffer != 0)
	{
		GlDeleteBuffers(1, &mVertexUVBuffer);
		mVertexUVBuffer = 0;
	}
}

void SpriteSheetRenderer::updateWindowSize(int width, int height)
{
	GlViewport(0, 0, width, height);
	mWindowWidth = width;
	mWindowHeight = height;
}

void SpriteSheetRenderer::clear() {
	GlClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	GlClear(GL_COLOR_BUFFER_BIT);
}

void SpriteSheetRenderer::drawSprite(shared_ptr<Sprite> sprite)
{
	this->drawSprite(sprite, sprite->position);
}

void SpriteSheetRenderer::drawSprite(shared_ptr<Sprite> sprite, Point<float> position)
{
	mShader->use();

	mShader->setInteger("tex", 0);

	GlActiveTexture(GL_TEXTURE0);
	GlBindTexture(GL_TEXTURE_2D, static_cast<GLuint>(2));

	GlEnable(GL_BLEND);
	GlBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GlTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	GlTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	GlBindBuffer(GL_ARRAY_BUFFER, mVertexPositionBuffer);
	GlVertexAttribPointer(mVertexAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
	GlEnableVertexAttribArray(mVertexAttribLocation);

	glm::mat4 projection = glm::ortho(0.0f, (float)mWindowWidth, 0.0f, (float)mWindowHeight, -1.0f, 1.0f); 
	mShader->setMatrix4("projection", projection);

	glm::mat4 world = glm::mat4(1.0f);
	world= glm::translate(world, glm::vec3(position.x, position.y, 0.0f)); 
	if(sprite->rotation != 0.0f) {
		world = glm::translate(world, glm::vec3(0.5f * sprite->texture.width, 0.5f * sprite->texture.height, 0.0f)); 
    	world = glm::rotate(world, glm::radians(sprite->rotation), glm::vec3(0.0f, 0.0f, 1.0f)); 
    	world = glm::translate(world, glm::vec3(-0.5f * sprite->texture.width, -0.5f * sprite->texture.height, 0.0f));		
	}
    world = glm::scale(world, glm::vec3(sprite->size.width, sprite->size.height, 1.0f));
	mShader->setMatrix4("world", world);

	GlBindBuffer(GL_ARRAY_BUFFER, mVertexUVBuffer);
	GlVertexAttribPointer(mUVAttribLocation, 2, GL_FLOAT, GL_FALSE, 2*sizeof(GL_FLOAT), BUFFER_OFFSET(sizeof(GL_FLOAT)*8));
	GlEnableVertexAttribArray(mUVAttribLocation);

	GLushort indices[] = { 0, 1, 3, 1, 2, 3 };
	GlDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
}

void SpriteSheetRenderer::initializeShaders() {
	auto resourceManager = IOCContainer::instance().resolve<IResourceManager>();
	mShader = resourceManager->getShader("spritesheet");
	auto id = mShader->ID;

	// Vertex shader parameters
	mVertexAttribLocation = GlGetAttribLocation(id, "vertex");
	mUVAttribLocation = GlGetAttribLocation(id, "a_uv");
	printf("Program with ID: %d attributes are fetched as: %d and %d\n", id, mVertexAttribLocation, mUVAttribLocation);
}

void SpriteSheetRenderer::initializeVertexBuffer()
{
	GLfloat vertexPositions[] =
	{
		 0.0f, 1.0f, 0.0f, 1.0f,
		 0.0f, 0.0f, 0.0f, 1.0f,
		 1.0f, 0.0f, 0.0f, 1.0f,
		 1.0f, 1.0f, 0.0f, 1.0f,
	};

	GlGenBuffers(1, &mVertexPositionBuffer);
	GlBindBuffer(GL_ARRAY_BUFFER, mVertexPositionBuffer);
	GlBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);
}

void SpriteSheetRenderer::addUVs(int x1, int y1, int x2, int y2)
{
	GLfloat width = 512.0;
	GLfloat height = 512.0;

	GLfloat s1 = x1 / width;
	GLfloat t1 = (height - y1) / height;
	GLfloat s2 = x2 / width;
	GLfloat t2 = (height - y2) / height;

	mUVVertices.push_back(s1);
	mUVVertices.push_back(t1);
	mUVVertices.push_back(s1);
	mUVVertices.push_back(t2);
	mUVVertices.push_back(s2);
	mUVVertices.push_back(t2);
	mUVVertices.push_back(s2);
	mUVVertices.push_back(t1);
}

void SpriteSheetRenderer::initializeUVBuffer() 
{
	GlGenBuffers(1, &mVertexUVBuffer);
	GlBindBuffer(GL_ARRAY_BUFFER, mVertexUVBuffer);
	GlBufferData(GL_ARRAY_BUFFER, mUVVertices.size() * sizeof(GLfloat), &mUVVertices.front(), GL_STATIC_DRAW);
}
