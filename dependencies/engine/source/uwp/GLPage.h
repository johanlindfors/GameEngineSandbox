#pragma once
#include <winrt/Windows.UI.Xaml.Controls.h>
#include <winrt/Windows.UI.Xaml.Media.h>
#include <winrt/Windows.UI.Xaml.Input.h>
#include <winrt/Windows.Foundation.h>
#include <memory>
#include "OpenGLES.h"
#include "GameLoop.h"
#include "input/IInputManager.h"

namespace Engine
{
    struct GLPage : winrt::Windows::UI::Xaml::Controls::PageT<GLPage> 
    {
        GLPage(std::shared_ptr<OpenGLES> openGLES);

	private:
		void CreateRenderSurface();
		void DestroyRenderSurface();
		void RenderLoop(winrt::Windows::Foundation::IAsyncAction const& action);
		void RecreateRenderer();

		// Event handlers
		void HandleKeyDown(const winrt::Windows::Foundation::IInspectable & sender, const winrt::Windows::UI::Xaml::Input::KeyRoutedEventArgs args);
		void HandleKeyUp(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::KeyRoutedEventArgs args);

		EGLSurface mRenderSurface; // This surface is associated with a swapChainPanel on the page
		std::shared_ptr<OpenGLES> mOpenGLES;
		std::unique_ptr<GameLoop> mGameLoop;
		std::shared_ptr<IInputManager> mInputManager;

		winrt::Windows::UI::Xaml::Controls::Grid mContentRoot;
		winrt::Windows::UI::Xaml::Controls::SwapChainPanel mSwapChainPanel;
    };
}