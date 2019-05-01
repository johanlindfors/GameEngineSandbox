#include "GLPage.h"
#include "IOC.hpp"
#include "IDispatcherWrapper.h"
#include "SetThreadName.h"

using std::shared_ptr;
using namespace Engine;
using namespace Utilities;

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
	
	mContentRoot = ref new Grid();
	mContentRoot->BorderThickness = Thickness(0);
	mContentRoot->Background = ref new SolidColorBrush(Colors::Black);

	mSwapChainPanel = ref new SwapChainPanel();
	mContentRoot->Children->Append(mSwapChainPanel);

	Content = mContentRoot;
	
	Loaded += ref new RoutedEventHandler(this, &GLPage::OnPageLoaded);
}

void GLPage::OnPageLoaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e) {
	// Run task on a dedicated high priority background thread
	ThreadPool::RunAsync(ref new WorkItemHandler(this, &GLPage::RenderLoop), WorkItemPriority::High, WorkItemOptions::TimeSliced);
}

void GLPage::OnKeyDown(KeyRoutedEventArgs ^ args)
{
	if (mInputManager)  {
		mInputManager->AddKeyboardEvent(static_cast<int>(args->Key), true);
	}	
}

void GLPage::OnKeyUp(KeyRoutedEventArgs ^ args)
{
	if (mInputManager) {
		mInputManager->AddKeyboardEvent(static_cast<int>(args->Key), false);
	}
}

void GLPage::RenderLoop(IAsyncAction ^ /*action*/)
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
			mGameLoop.reset(nullptr);
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
        mGameLoop->Initialize();

		if (mInputManager == nullptr) {
			mInputManager = IOCContainer::Instance().Resolve<IInputManager>();
		}
	}
}
