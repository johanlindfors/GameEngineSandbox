#pragma once
#include <memory>
#include "OpenGLES.h"
#include "input/IInputManager.h"
#include "game-loop/GameLoop.h"

namespace Engine
{
    ref class GLPage sealed : Windows::UI::Xaml::Controls::Page 
    {
	internal:
        GLPage(std::shared_ptr<OpenGLES> openGLES);

	public:
		// Event handlers
		void OnKeyDown(Windows::UI::Xaml::Input::KeyRoutedEventArgs^ args) override;
		void OnKeyUp(Windows::UI::Xaml::Input::KeyRoutedEventArgs ^ args) override;

	private:
		void OnPageLoaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void RenderLoop(Windows::Foundation::IAsyncAction^ action);
		void RecreateRenderer();

		std::shared_ptr<OpenGLES> mOpenGLES;
		std::unique_ptr<GameLoop> mGameLoop;
		std::shared_ptr<IInputManager> mInputManager;

		Windows::UI::Xaml::Controls::Grid ^ mContentRoot;
		Windows::UI::Xaml::Controls::SwapChainPanel ^ mSwapChainPanel;
    };
}