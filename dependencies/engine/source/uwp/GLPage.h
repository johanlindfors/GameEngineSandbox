#pragma once
#include <winrt/Windows.UI.Xaml.Controls.h>
#include <winrt/Windows.UI.Xaml.Media.h>
#include <winrt/Windows.Foundation.h>
#include <memory>
#include "OpenGLES.h"
#include "GameLoop.h"

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

		EGLSurface mRenderSurface; // This surface is associated with a swapChainPanel on the page
		std::shared_ptr<OpenGLES> mOpenGLES;
		std::unique_ptr<GameLoop> mGameLoop;

		winrt::Windows::UI::Xaml::Controls::Grid mContentRoot;
		winrt::Windows::UI::Xaml::Controls::SwapChainPanel mSwapChainPanel;
    };
}