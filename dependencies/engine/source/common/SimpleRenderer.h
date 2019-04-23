#pragma once
#include "glwrapper.h"
#include "IStepTimer.h"

namespace Engine
{
    class SimpleRenderer
    {
    public:
        SimpleRenderer();
        ~SimpleRenderer();
		void Draw(std::shared_ptr<Utilities::IStepTimer> timer);
		void Update(std::shared_ptr<Utilities::IStepTimer> timer);
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