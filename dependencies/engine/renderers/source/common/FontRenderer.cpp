#include "renderers/FontRenderer.h"
#include "resources/IResourceManager.h"
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

FontRenderer::FontRenderer(const string& atlasFilename)
	: mAtlasFilename(atlasFilename)
	, mShader(make_unique<Shader>())
	, mInitialized(false)
{ }

void FontRenderer::LazyInitialize() {
	InitializeShaders();
	InitializeVertexBuffer();

	auto filesystem = IOCContainer::Instance().Resolve<IFileSystem>();
	auto file = filesystem->LoadFile(mAtlasFilename, false);
	if(file->IsOpen()) {
		int id, x, y, width, height, xoffset, yoffset, xadvance;
		char buffer[100];
		auto fileHandle = file->Get();
		int offset = 0;
		while(!feof(fileHandle)) {
    	    fscanf(fileHandle, "%d:%d,%d,%d,%d,%d,%d,%d", &id, &x, &y, &width, &height, &xoffset, &yoffset, &xadvance);
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

void FontRenderer::UpdateWindowSize(int width, int height)
{
	glViewport(0, 0, width, height);
	mWindowWidth = width;
	mWindowHeight = height;
}

void FontRenderer::DrawString(const string& str, Utilities::Point<float> centerPosition, float scale)
{
	auto dimensions = MeasureString(str);
	int x = centerPosition.X - dimensions.Width/2 * scale;
	int y = centerPosition.Y - dimensions.Height/2 * scale;
	for(const auto& character : str) {
		auto characterToDraw = mCharacters[character];
 		DrawCharacter(characterToDraw.UVOffset, Utilities::Rectangle(x, y, characterToDraw.Width * scale, characterToDraw.Height * scale));
		x += characterToDraw.XAdvance * scale;
	}
}

Utilities::Rectangle FontRenderer::MeasureString(const string& str) 
{
	auto dimensions = Utilities::Rectangle(0,0,0,63);
	for(const auto& character : str) {
		dimensions.Width += mCharacters[character].XAdvance;
	}
	return dimensions;
}

void FontRenderer::DrawCharacter(int offset, Utilities::Rectangle rectangle)
{
	mShader->Use();

	mShader->SetInteger("texture", 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, static_cast<GLuint>(2));

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glBindBuffer(GL_ARRAY_BUFFER, mVertexPositionBuffer);
	glEnableVertexAttribArray(mVertexAttribLocation);
	glVertexAttribPointer(mVertexAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, nullptr);

	glm::mat4 projection = glm::ortho(0.0f, (float)mWindowWidth, 0.0f, (float)mWindowHeight, -1.0f, 1.0f); 
	mShader->SetMatrix4("projection", projection);

	glm::mat4 world = glm::mat4(1.0f);
	world= glm::translate(world, glm::vec3(rectangle.Position.X, rectangle.Position.Y, 0.0f));
	world = glm::scale(world, glm::vec3(rectangle.Width, rectangle.Height, 1.0f));
	mShader->SetMatrix4("world", world);

	glBindBuffer(GL_ARRAY_BUFFER, mVertexUVBuffer);
	glEnableVertexAttribArray(mUVAttribLocation);
	glVertexAttribPointer(mUVAttribLocation, 2, GL_FLOAT, GL_FALSE, 2*sizeof(GL_FLOAT), BUFFER_OFFSET(sizeof(GL_FLOAT)*offset*8));

	GLushort indices[] = { 0, 1, 3, 1, 2, 3 };
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
}

void FontRenderer::InitializeShaders() {
	auto resourceManager = IOCContainer::Instance().Resolve<IResourceManager>();
	mShader = resourceManager->GetShader("fontsheet");
	auto id = mShader->ID;

	// Vertex shader parameters
	mVertexAttribLocation = 0;// GlGetAttribLocation(id, "vertex");
	mUVAttribLocation = 1;// GlGetAttribLocation(id, "a_uv");
	printf("Program with ID: %d attributes are fetched as: %d and %d\n", id, mVertexAttribLocation, mUVAttribLocation);
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

	GlGenBuffers(1, &mVertexPositionBuffer);
	GlBindBuffer(GL_ARRAY_BUFFER, mVertexPositionBuffer);
	GlBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);
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
	GlGenBuffers(1, &mVertexUVBuffer);
	GlBindBuffer(GL_ARRAY_BUFFER, mVertexUVBuffer);
	GlBufferData(GL_ARRAY_BUFFER, mUVVertices.size() * sizeof(GLfloat), &mUVVertices.front(), GL_STATIC_DRAW);
}

void FontRenderer::AddCharacter(int id, int x, int y, int width, int height, int xoffset, int yoffset, int xadvance, int offset)
{	
	auto character = Character();
	character.CharacterCode = id;
	character.UVOffset = offset;
	character.XAdvance = xadvance;
	character.XOffset = xoffset;
	character.YOffset = yoffset;
	character.Width = width;
	character.Height = height;

	AddUVs(x,y, x + width, y + height);
	mCharacters[(char)id] = character; 
}
