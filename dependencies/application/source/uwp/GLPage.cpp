#include "GLPage.h"
#include <winrt/Windows.Graphics.Display.h>
#include <winrt/Windows.System.Threading.h>
#include <winrt/Windows.UI.Input.h>
#include "IOC.hpp"
#include "DispatcherWrapper.h"
#include "SetThreadName.h"

#include <winrt/Windows.ApplicationModel.h>
#include <winrt/Windows.Devices.Input.h>
#include <winrt/Windows.Foundation.Metadata.h>
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.System.h>
#include <winrt/Windows.UI.h>
#include <winrt/Windows.UI.Composition.h>
#include <winrt/Windows.UI.Core.h>
#include <winrt/Windows.UI.ViewManagement.h>
#include <winrt/Windows.UI.Xaml.h>
#include <winrt/Windows.UI.Xaml.Hosting.h>
#include <winrt/Windows.UI.Xaml.Media.h>
#include <winrt/Windows.UI.Xaml.Media.Imaging.h>
#include <winrt/Windows.UI.Xaml.Navigation.h>


using std::shared_ptr;
using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::UI;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Core;
using namespace Windows::Graphics::Display;
using namespace Windows::System::Threading;
using namespace Windows::System;
using namespace Engine;
using namespace Utilities;



GLPage::GLPage(shared_ptr<OpenGLES> openGLES) 
	: mOpenGLES(openGLES)
{
	SetThreadName((DWORD)-1, "UI Thread");
	
	mContentRoot.BorderThickness(Thickness{ 0 });
	mContentRoot.Background(SolidColorBrush(Colors::Black()));
	mContentRoot.Children().Append(mSwapChainPanel);

	Content(mContentRoot);
	
	Loaded([=](auto, auto) {
		// Run task on a dedicated high priority background thread
		ThreadPool::RunAsync(WorkItemHandler(this, &GLPage::RenderLoop), WorkItemPriority::High, WorkItemOptions::TimeSliced);
	});

	KeyDown(KeyEventHandler(this, &GLPage::HandleKeyDown));
	KeyUp(KeyEventHandler(this, &GLPage::HandleKeyUp));

}

void GLPage::HandleKeyDown(const IInspectable & sender, const KeyRoutedEventArgs args)
{
	if (mInputManager == nullptr) {
		mInputManager = IOCContainer::Instance().Resolve<IInputManager>();
	}
	mInputManager->AddKeyboardEvent(static_cast<int>(args.Key()), true);
}

void GLPage::HandleKeyUp(IInspectable const& sender, KeyRoutedEventArgs args)
{
	if (mInputManager == nullptr) {
		mInputManager = IOCContainer::Instance().Resolve<IInputManager>();
	}
	mInputManager->AddKeyboardEvent(static_cast<int>(args.Key()), false);
}

void GLPage::RenderLoop(IAsyncAction const& /*action*/)
{
	auto dispatcher = IOCContainer::Instance().Resolve<DispatcherWrapper>();
	
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
	}
}
