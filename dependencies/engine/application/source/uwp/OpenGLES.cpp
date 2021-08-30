#include "OpenGLES.h"

#define ANGLE_ERROR(id, text) hresult_error(id, text);

using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Engine;

OpenGLES::OpenGLES()
	: mEglDisplay(EGL_NO_DISPLAY), mEglContext(EGL_NO_CONTEXT), mEglConfig(nullptr) {
}

OpenGLES::~OpenGLES() {
	Cleanup();
}

void OpenGLES::Initialize() {
	const EGLint configAttributes[] =
	{
		EGL_RED_SIZE, 8,
		EGL_GREEN_SIZE, 8,
		EGL_BLUE_SIZE, 8,
		EGL_ALPHA_SIZE, 8,
		EGL_DEPTH_SIZE, 8,
		EGL_STENCIL_SIZE, 8,
		EGL_NONE
	};

	const EGLint contextAttributes[] =
	{
		EGL_CONTEXT_CLIENT_VERSION, 2,
		EGL_NONE
	};

	const EGLint defaultDisplayAttributes[] =
	{
		// These are the default display attributes, used to request ANGLE's D3D11 renderer.
		// eglInitialize will only succeed with these attributes if the hardware supports D3D11 Feature Level 10_0+.
		EGL_PLATFORM_ANGLE_TYPE_ANGLE,
		EGL_PLATFORM_ANGLE_TYPE_D3D11_ANGLE,

		// EGL_ANGLE_DISPLAY_ALLOW_RENDER_TO_BACK_BUFFER is an optimization that can have large performance benefits on mobile devices.
		// Its syntax is subject to change, though. Please update your Visual Studio templates if you experience compilation issues with it.
		EGL_ANGLE_DISPLAY_ALLOW_RENDER_TO_BACK_BUFFER,
		EGL_TRUE,

		// EGL_PLATFORM_ANGLE_ENABLE_AUTOMATIC_TRIM_ANGLE is an option that enables ANGLE to automatically call
		// the IDXGIDevice3::Trim method on behalf of the application when it gets suspended.
		// Calling IDXGIDevice3::Trim when an application is suspended is a Windows Store application certification requirement.
		EGL_PLATFORM_ANGLE_ENABLE_AUTOMATIC_TRIM_ANGLE,
		EGL_TRUE,
		EGL_NONE,
	};

	const EGLint fl9_3DisplayAttributes[] =
	{
		// These can be used to request ANGLE's D3D11 renderer, with D3D11 Feature Level 9_3.
		// These attributes are used if the call to eglInitialize fails with the default display attributes.
		EGL_PLATFORM_ANGLE_TYPE_ANGLE,
		EGL_PLATFORM_ANGLE_TYPE_D3D11_ANGLE,
		EGL_PLATFORM_ANGLE_MAX_VERSION_MAJOR_ANGLE,
		9,
		EGL_PLATFORM_ANGLE_MAX_VERSION_MINOR_ANGLE,
		3,
		EGL_ANGLE_DISPLAY_ALLOW_RENDER_TO_BACK_BUFFER,
		EGL_TRUE,
		EGL_PLATFORM_ANGLE_ENABLE_AUTOMATIC_TRIM_ANGLE,
		EGL_TRUE,
		EGL_NONE,
	};

	const EGLint warpDisplayAttributes[] =
	{
		// These attributes can be used to request D3D11 WARP.
		// They are used if eglInitialize fails with both the default display attributes and the 9_3 display attributes.
		EGL_PLATFORM_ANGLE_TYPE_ANGLE,
		EGL_PLATFORM_ANGLE_TYPE_D3D11_ANGLE,
		EGL_PLATFORM_ANGLE_DEVICE_TYPE_ANGLE,
		EGL_PLATFORM_ANGLE_DEVICE_TYPE_WARP_ANGLE,
		EGL_ANGLE_DISPLAY_ALLOW_RENDER_TO_BACK_BUFFER,
		EGL_TRUE,
		EGL_PLATFORM_ANGLE_ENABLE_AUTOMATIC_TRIM_ANGLE,
		EGL_TRUE,
		EGL_NONE,
	};

	// eglGetPlatformDisplayEXT is an alternative to eglGetDisplay. It allows us to pass in display attributes, used to configure D3D11.
	const PFNEGLGETPLATFORMDISPLAYEXTPROC eglGetPlatformDisplayEXT = reinterpret_cast<PFNEGLGETPLATFORMDISPLAYEXTPROC>(eglGetProcAddress("eglGetPlatformDisplayEXT"));
	if (!eglGetPlatformDisplayEXT) {
		throw ANGLE_ERROR(E_FAIL, L"Failed to get function eglGetPlatformDisplayEXT");
	}

	//
	// To initialize the display, we make three sets of calls to eglGetPlatformDisplayEXT and eglInitialize, with varying
	// parameters passed to eglGetPlatformDisplayEXT:
	// 1) The first calls uses "defaultDisplayAttributes" as a parameter. This corresponds to D3D11 Feature Level 10_0+.
	// 2) If eglInitialize fails for step 1 (e.g. because 10_0+ isn't supported by the default GPU), then we try again
	//    using "fl9_3DisplayAttributes". This corresponds to D3D11 Feature Level 9_3.
	// 3) If eglInitialize fails for step 2 (e.g. because 9_3+ isn't supported by the default GPU), then we try again
	//    using "warpDisplayAttributes".  This corresponds to D3D11 Feature Level 11_0 on WARP, a D3D11 software rasterizer.
	//
	// Note: On Windows Phone, we #ifdef out the first set of calls to eglPlatformDisplayEXT and eglInitialize.
	//       Windows Phones devices only support D3D11 Feature Level 9_3, but the Windows Phone emulator supports 11_0+.
	//       We use this #ifdef to limit the Phone emulator to Feature Level 9_3, making it behave more like
	//       real Windows Phone devices.
	//       If you wish to test Feature Level 10_0+ in the Windows Phone emulator then you should remove this #ifdef.
	//

	// This tries to initialize EGL to D3D11 Feature Level 10_0+. See above comment for details.
	mEglDisplay = eglGetPlatformDisplayEXT(EGL_PLATFORM_ANGLE_ANGLE, EGL_DEFAULT_DISPLAY, defaultDisplayAttributes);
	if (mEglDisplay == EGL_NO_DISPLAY) {
		throw ANGLE_ERROR(E_FAIL, L"Failed to get EGL display");
	}

	if (eglInitialize(mEglDisplay, nullptr, nullptr) == EGL_FALSE) {
		// This tries to initialize EGL to D3D11 Feature Level 9_3, if 10_0+ is unavailable (e.g. on some mobile devices).
		mEglDisplay = eglGetPlatformDisplayEXT(EGL_PLATFORM_ANGLE_ANGLE, EGL_DEFAULT_DISPLAY, fl9_3DisplayAttributes);
		if (mEglDisplay == EGL_NO_DISPLAY) {
			throw ANGLE_ERROR(E_FAIL, L"Failed to get EGL display");
		}

		if (eglInitialize(mEglDisplay, nullptr, nullptr) == EGL_FALSE) {
			// This initializes EGL to D3D11 Feature Level 11_0 on WARP, if 9_3+ is unavailable on the default GPU.
			mEglDisplay = eglGetPlatformDisplayEXT(EGL_PLATFORM_ANGLE_ANGLE, EGL_DEFAULT_DISPLAY, warpDisplayAttributes);
			if (mEglDisplay == EGL_NO_DISPLAY) {
				throw ANGLE_ERROR(E_FAIL, L"Failed to get EGL display");
			}

			if (eglInitialize(mEglDisplay, nullptr, nullptr) == EGL_FALSE) {
				// If all of the calls to eglInitialize returned EGL_FALSE then an error has occurred.
				throw ANGLE_ERROR(E_FAIL, L"Failed to initialize EGL");
			}
		}
	}

	EGLint numConfigs = 0;
	if ((eglChooseConfig(mEglDisplay, configAttributes, &mEglConfig, 1, &numConfigs) == EGL_FALSE) || (numConfigs == 0)) {
		throw ANGLE_ERROR(E_FAIL, L"Failed to choose first EGLConfig");
	}

	mEglContext = eglCreateContext(mEglDisplay, mEglConfig, EGL_NO_CONTEXT, contextAttributes);
	if (mEglContext == EGL_NO_CONTEXT) {
		throw ANGLE_ERROR(E_FAIL, L"Failed to create EGL context");
	}
}

void OpenGLES::Cleanup() {
	if (mEglDisplay != EGL_NO_DISPLAY && mEglContext != EGL_NO_CONTEXT) {
		eglDestroyContext(mEglDisplay, mEglContext);
		mEglContext = EGL_NO_CONTEXT;
	}

	if (mEglDisplay != EGL_NO_DISPLAY) {
		eglTerminate(mEglDisplay);
		mEglDisplay = EGL_NO_DISPLAY;
	}
}

void OpenGLES::GetSurfaceDimensions(const EGLSurface surface, EGLint* width, EGLint* height) const
{
	eglQuerySurface(mEglDisplay, surface, EGL_WIDTH, width);
	eglQuerySurface(mEglDisplay, surface, EGL_HEIGHT, height);
}

void OpenGLES::Reset() {
	Cleanup();
	Initialize();
}

EGLSurface OpenGLES::CreateSurface(Windows::Foundation::IInspectable const& panel, const Size* renderSurfaceSize, const float* resolutionScale) const
{
	if (!panel) {
		throw ANGLE_ERROR(E_INVALIDARG, L"SwapChainPanel parameter is invalid");
	}

	if (renderSurfaceSize != nullptr && resolutionScale != nullptr) {
		throw ANGLE_ERROR(E_INVALIDARG, L"A size and a scale can't both be specified");
	}

	const EGLint surfaceAttributes[] =
	{
		// EGL_ANGLE_SURFACE_RENDER_TO_BACK_BUFFER is part of the same optimization as EGL_ANGLE_DISPLAY_ALLOW_RENDER_TO_BACK_BUFFER (see above).
		// If you have compilation issues with it then please update your Visual Studio templates.
		EGL_ANGLE_SURFACE_RENDER_TO_BACK_BUFFER, EGL_TRUE,
		EGL_NONE
	};

	// Create a PropertySet and initialize with the EGLNativeWindowType.
	const PropertySet surfaceCreationProperties;
	surfaceCreationProperties.Insert(hstring(EGLNativeWindowTypeProperty), panel);

	// If a render surface size is specified, add it to the surface creation properties
	if (renderSurfaceSize != nullptr) {
		surfaceCreationProperties.Insert(hstring(EGLRenderSurfaceSizeProperty), PropertyValue::CreateSize(*renderSurfaceSize));
	}

	// If a resolution scale is specified, add it to the surface creation properties
	if (resolutionScale != nullptr) {
		surfaceCreationProperties.Insert(hstring(EGLRenderResolutionScaleProperty), PropertyValue::CreateSingle(*resolutionScale));
	}

	const auto parameters = static_cast<::IInspectable*>(winrt::get_abi(surfaceCreationProperties));

	const auto surface = eglCreateWindowSurface(mEglDisplay, mEglConfig, parameters, surfaceAttributes);
	if (surface == EGL_NO_SURFACE) {
		throw ANGLE_ERROR(E_FAIL, L"Failed to create EGL surface");
	}

	return surface;
}

void OpenGLES::DestroySurface(const EGLSurface surface) const
{
	if (mEglDisplay != EGL_NO_DISPLAY && surface != EGL_NO_SURFACE) {
		eglDestroySurface(mEglDisplay, surface);
	}
}

void OpenGLES::MakeCurrent(const EGLSurface surface) const
{
	if (eglMakeCurrent(mEglDisplay, surface, surface, mEglContext) == EGL_FALSE) {
		throw ANGLE_ERROR(E_FAIL, L"Failed to make EGLSurface current");
	}
}

EGLBoolean OpenGLES::SwapBuffers(const EGLSurface surface) const
{
	return (eglSwapBuffers(mEglDisplay, surface));
}
