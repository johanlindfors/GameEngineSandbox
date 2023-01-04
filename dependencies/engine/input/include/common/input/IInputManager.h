#pragma once

namespace Engine {
	class IInputManager {
	public:
		virtual ~IInputManager() = default;
		virtual void addKeyboardEvent(int keyCode, bool isPressed) = 0;
		virtual bool isKeyDown(int keyCode) = 0;
	};
}
