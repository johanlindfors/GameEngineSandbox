#pragma once
#include "glwrapper.h"

namespace Engine
{
    class SimpleRenderer
    {
    public:
        SimpleRenderer();
        ~SimpleRenderer();
		void Draw();
		void Update();
        void UpdateWindowSize(GLsizei width, GLsizei height);

    private:
        GLuint mProgram;
        GLsizei mWindowWidth;
        GLsizei mWindowHeight;

        GLint mPositionAttribLocation;
        GLint mColorAttribLocation;

        GLint mModelUniformLocation;
        GLint mViewUniformLocation;
        GLint mProjUniformLocation;

        GLuint mVertexPositionBuffer;
        GLuint mVertexColorBuffer;
        GLuint mIndexBuffer;

        int mDrawCount;
    };
}