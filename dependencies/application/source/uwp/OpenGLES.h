#pragma once

#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.UI.Xaml.Controls.h>

// OpenGL ES includes
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

// EGL includes
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/eglplatform.h>

namespace Engine {
	class OpenGLES {
	public:
		OpenGLES();
		virtual ~OpenGLES();

		void Initialize();
		EGLSurface CreateSurface(winrt::Windows::Foundation::IInspectable const& panel, const winrt::Windows::Foundation::Size* renderSurfaceSize, const float* renderResolutionScale);
		void GetSurfaceDimensions(const EGLSurface surface, EGLint* width, EGLint* height);
		void DestroySurface(const EGLSurface surface);
		void MakeCurrent(const EGLSurface surface);
		EGLBoolean SwapBuffers(const EGLSurface surface);
		void Reset();
		void Cleanup();

	private:
		EGLDisplay mEglDisplay;
		EGLContext mEglContext;
		EGLConfig mEglConfig;
	};
}
