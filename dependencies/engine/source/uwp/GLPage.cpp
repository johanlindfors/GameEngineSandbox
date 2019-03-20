#include "GLPage.h"
#include <winrt/Windows.Graphics.Display.h>
#include <winrt/Windows.System.Threading.h>

using std::shared_ptr;
using namespace Engine;
using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::UI;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Core;
using namespace Windows::Graphics::Display;
using namespace Windows::System::Threading;

#define SCALE_FACTOR 1.0f

GLPage::GLPage(shared_ptr<OpenGLES> openGLES) 
	: mOpenGLES(openGLES)
{
	mContentRoot.BorderThickness(Thickness{ 0 });
	mContentRoot.Background(SolidColorBrush(Colors::Black()));
	mContentRoot.Children().Append(mSwapChainPanel);

	Content(mContentRoot);
	
	Loaded([=](auto, auto) {
		// Run task on a dedicated high priority background thread
		ThreadPool::RunAsync(WorkItemHandler(this, &GLPage::RenderLoop), WorkItemPriority::High, WorkItemOptions::TimeSliced);
	});
}

void GLPage::CreateRenderSurface()
{
	if (mOpenGLES) {
		mRenderSurface = mOpenGLES->CreateSurface(mSwapChainPanel, nullptr, nullptr);
	}
}

void GLPage::RenderLoop(IAsyncAction const& /*action*/)
{
	mOpenGLES->Initialize();
	CreateRenderSurface();
	mOpenGLES->MakeCurrent(mRenderSurface);

	RecreateRenderer();

	while (true) {
		EGLint panelWidth = 0;
		EGLint panelHeight = 0;
		mOpenGLES->GetSurfaceDimensions(mRenderSurface, &panelWidth, &panelHeight);
		mGameLoop->OnWindowSizeChanged(panelWidth, panelHeight);
		mGameLoop->Tick();

		if (mOpenGLES->SwapBuffers(mRenderSurface) != GL_TRUE)
		{
			mGameLoop.reset(nullptr);
			RecreateRenderer();
		}
	}

	DestroyRenderSurface();
}

void GLPage::DestroyRenderSurface()
{
	if (mOpenGLES) {
		mOpenGLES->DestroySurface(mRenderSurface);
	}
	mRenderSurface = EGL_NO_SURFACE;
}

void GLPage::RecreateRenderer()
{
	if (!mGameLoop)
	{
		mGameLoop.reset(new GameLoop());
	}
}
