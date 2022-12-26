#include "renderers/FontRenderer.h"
#include <string>
#include "utilities/MathHelper.h"
#include "utilities/GLHelper.h"
#include "renderers/Sprite.h"
#include "filesystem/IFileSystem.h"
#include "utilities/IOC.hpp"
#include "File.h"
#include "resources/Shader.h"

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/vec2.hpp>
#include <vector>

#define STRING(s) #s
#define BUFFER_OFFSET(i) ((void*)(i))

using namespace std;
using namespace Engine;
using namespace Utilities;

FontRenderer::FontRenderer(string textureFilename, string atlasFilename)
	: mTextureFilename(textureFilename)
	, mAtlasFilename(atlasFilename)
	, mShader(make_unique<Shader>())
	, mInitialized(false)
{ }

void FontRenderer::Initialize()
{
	InitializeShaders();
	InitializeVertexBuffer();

	auto filesystem = IOCContainer::Instance().Resolve<IFileSystem>();
	auto file = filesystem->LoadFile(mAtlasFilename);
	if(file->IsOpen()) {
		int id, x, y, width, height, xoffset, yoffset, xadvance;
		char buffer[100];
		auto fileHandle = file->Get();
		int offset = 0;
		while(!feof(fileHandle)) {
    	    fscanf(fileHandle, "%d:%d,%d,%d,%d,%d,%d,%d", &x, &y, &width, &height, &xoffset, &yoffset, &xadvance);
			AddCharacter(id, x, y, width, height, xoffset, yoffset, xadvance, offset++);
	        fgets(buffer, 100, fileHandle); // skip the rest of the line
		}
    }
    
	InitializeUVBuffer();
}

FontRenderer::~FontRenderer()
{
	mShader.reset();

	if (mVertexPositionBuffer != 0)
	{
		glDeleteBuffers(1, &mVertexPositionBuffer);
		mVertexPositionBuffer = 0;
	}

	if (mVertexUVBuffer != 0)
	{
		glDeleteBuffers(1, &mVertexUVBuffer);
		mVertexUVBuffer = 0;
	}
}

void FontRenderer::UpdateWindowSize(GLsizei width, GLsizei height)
{
	glViewport(0, 0, width, height);
	mWindowWidth = width;
	mWindowHeight = height;
}

void FontRenderer::Clear() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void FontRenderer::DrawSprite(shared_ptr<Sprite> sprite)
{
	this->DrawSprite(sprite, sprite->Position);
}

void FontRenderer::DrawSprite(shared_ptr<Sprite> sprite, Point<float> position)
{
	mShader->Use();

	mShader->SetInteger("texture", 0);

	if(!mInitialized) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, static_cast<GLuint>(2));

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glBindBuffer(GL_ARRAY_BUFFER, mVertexPositionBuffer);
		glEnableVertexAttribArray(mVertexAttribLocation);
		glVertexAttribPointer(mVertexAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, nullptr);

		mInitialized = true;
	}

	glm::mat4 projection = glm::ortho(0.0f, (float)mWindowWidth, 0.0f, (float)mWindowHeight, -1.0f, 1.0f); 
	mShader->SetMatrix4("projection", projection);

	glm::mat4 world = glm::mat4(1.0f);
	world= glm::translate(world, glm::vec3(position.X, position.Y, 0.0f)); 
	if(sprite->Rotation != 0.0f) {
		world = glm::translate(world, glm::vec3(0.5f * sprite->Texture.Width, 0.5f * sprite->Texture.Height, 0.0f)); 
    	world = glm::rotate(world, glm::radians(sprite->Rotation), glm::vec3(0.0f, 0.0f, 1.0f)); 
    	world = glm::translate(world, glm::vec3(-0.5f * sprite->Texture.Width, -0.5f * sprite->Texture.Height, 0.0f));		
	}
    world = glm::scale(world, glm::vec3(sprite->Width, sprite->Height, 1.0f));
	mShader->SetMatrix4("world", world);

	glBindBuffer(GL_ARRAY_BUFFER, mVertexUVBuffer);
	glEnableVertexAttribArray(mUVAttribLocation);
	glVertexAttribPointer(mUVAttribLocation, 2, GL_FLOAT, GL_FALSE, 2*sizeof(GL_FLOAT), BUFFER_OFFSET(sizeof(GL_FLOAT)*sprite->Offset*8));

	GLushort indices[] = { 0, 1, 3, 1, 2, 3 };
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
}

void FontRenderer::InitializeShaders() {
	// Vertex Shader source
	const std::string vs = STRING
	(
		attribute vec4 vertex; // <vec2 position, vec2 texCoords>
		attribute vec2 a_uv;
		
		uniform mat4 world;
		uniform mat4 projection;

		varying vec2 TexCoords;

		void main()
		{
			TexCoords = a_uv;
			gl_Position = projection * world * vertex;
		}
	);

	// Fragment Shader source
	const std::string fs = STRING
	(
#ifndef __APPLE__
		precision mediump float;
#endif
		varying vec2 TexCoords;

		uniform sampler2D texture;
		
		void main()
		{
			gl_FragColor = texture2D(texture, TexCoords);
		}
	);

	mShader->CreateShader("atlas", vs, fs);

	// Vertex shader parameters
	mVertexAttribLocation = glGetAttribLocation(mShader->ID, "vertex");
	mUVAttribLocation = glGetAttribLocation(mShader->ID, "a_uv");
}

void FontRenderer::InitializeVertexBuffer()
{
	GLfloat vertexPositions[] =
	{
		 0.0f, 1.0f, 0.0f, 1.0f,
		 0.0f, 0.0f, 0.0f, 1.0f,
		 1.0f, 0.0f, 0.0f, 1.0f,
		 1.0f, 1.0f, 0.0f, 1.0f,
	};

	glGenBuffers(1, &mVertexPositionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexPositionBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);
}

void FontRenderer::AddCharacter(int id, int x, int y, int width, int height, int xoffset, int yoffset, int xadvance, int offset)
{	
	auto character = Character();
	character.CharacterCode = id;
	character.UVOffset = offset;
	character.XAdvance = xadvance;
	character.XOffset = xoffset;
	character.YOffset = yoffset;

	AddUVs(x,y, x + width, y + height);
	mCharacters[(char)id] = character; 
}

void FontRenderer::AddUVs(int x1, int y1, int x2, int y2)
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

void FontRenderer::InitializeUVBuffer() 
{
	glGenBuffers(1, &mVertexUVBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexUVBuffer);
	glBufferData(GL_ARRAY_BUFFER, mUVVertices.size() * sizeof(GLfloat), &mUVVertices.front(), GL_STATIC_DRAW);
}
