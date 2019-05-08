#include "GLPage.h"
#include "IOC.hpp"
#include "IDispatcherWrapper.h"
#include "SetThreadName.h"
#include "game-loop/GameLoop.h"
#include <winrt/Windows.System.Threading.h>
#include "application/Config.h"

using std::shared_ptr;
using namespace Engine;
using namespace Utilities;

using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::UI;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::System::Threading;

GLPage::GLPage(shared_ptr<OpenGLES> openGLES) 
	: mOpenGLES(openGLES)
{
	SetThreadName((DWORD)-1, "UI Thread");
	
	mContentRoot.BorderThickness(Thickness{ 0 });
	mContentRoot.Background(SolidColorBrush(Colors::Black()));
	mContentRoot.Children().Append(mSwapChainPanel);

	Content(mContentRoot);
	
	Loaded({ this, &GLPage::OnPageLoaded });
}

void GLPage::OnPageLoaded(IInspectable const&, RoutedEventArgs const&) 
{
	// Run task on a dedicated high priority background thread
	ThreadPool::RunAsync(WorkItemHandler(this, &GLPage::RenderLoop), WorkItemPriority::High, WorkItemOptions::TimeSliced);
}

void GLPage::OnKeyDown(KeyRoutedEventArgs const& args) const
{
	if (mInputManager) {
		mInputManager->AddKeyboardEvent(static_cast<int>(args.Key()), true);
	}
}

void GLPage::OnKeyUp(KeyRoutedEventArgs const& args) const
{
	if (mInputManager) {
		mInputManager->AddKeyboardEvent(static_cast<int>(args.Key()), false);
	}
}

void GLPage::RenderLoop(IAsyncAction const& /*action*/)
{
	auto dispatcher = IOCContainer::Instance().Resolve<IDispatcherWrapper>();
	
	SetThreadName((DWORD)-1, "Game Thread");
	
	mOpenGLES->Initialize();
	auto renderSurface = mOpenGLES->CreateSurface(mSwapChainPanel, nullptr, nullptr);
	mOpenGLES->MakeCurrent(renderSurface);

	RecreateRenderer();

	while (true) {
		EGLint panelWidth = 0;
		EGLint panelHeight = 0;

		mOpenGLES->GetSurfaceDimensions(renderSurface, &panelWidth, &panelHeight);
		mGameLoop->UpdateWindowSize(panelWidth, panelHeight);
		mGameLoop->Tick();

		if (mOpenGLES->SwapBuffers(renderSurface) != GL_TRUE)
		{
			RecreateRenderer();
		}
		dispatcher->ProcessScheduledFunctions();
	}

	if (mOpenGLES) {
		mOpenGLES->DestroySurface(renderSurface);
	}
}

void GLPage::RecreateRenderer()
{
	if (!mGameLoop)
	{
		mGameLoop.reset(new GameLoop());
		auto config = IOCContainer::Instance().Resolve<Config>();
        mGameLoop->Initialize(config->FPS);

		if (mInputManager == nullptr) {
			mInputManager = IOCContainer::Instance().Resolve<IInputManager>();
		}
	}
}
