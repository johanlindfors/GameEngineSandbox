#pragma once

namespace Engine {
	class IInputManager {
	public:
		virtual ~IInputManager() = default;
		virtual void AddKeyboardEvent(int keyCode, bool isPressed) = 0;
		virtual bool IsKeyDown(int keyCode) = 0;
	};
}
