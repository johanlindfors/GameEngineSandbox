#pragma once
#include "MouseStates.h"

namespace Engine {
	class IInputManager {
	public:
		virtual ~IInputManager() = default;
		virtual void AddKeyboardEvent(int keyCode, bool isPressed) = 0;
		virtual void AddMouseEvent(MouseButton button, MouseButtonState action, int x, int y) = 0;
		virtual bool IsKeyDown(int keyCode) = 0;
		virtual MouseState GetMouseState() = 0;
		virtual void Update() = 0;
	};
}
