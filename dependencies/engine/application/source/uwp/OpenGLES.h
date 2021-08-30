#pragma once
#include <winrt/Windows.Foundation.Collections.h>
#include "glwrapper.h"

namespace Engine {
	class OpenGLES {
	public:
		OpenGLES();
		virtual ~OpenGLES();

		void Initialize();
		EGLSurface CreateSurface(winrt::Windows::Foundation::IInspectable const& panel, const winrt::Windows::Foundation::Size* renderSurfaceSize, const float* renderResolutionScale) const;
		void GetSurfaceDimensions(const EGLSurface surface, EGLint* width, EGLint* height) const;
		void DestroySurface(const EGLSurface surface) const;
		void MakeCurrent(const EGLSurface surface) const;
		EGLBoolean SwapBuffers(const EGLSurface surface) const;
		void Reset();
		void Cleanup();

	private:
		EGLDisplay mEglDisplay;
		EGLContext mEglContext;
		EGLConfig mEglConfig;
	};
}
