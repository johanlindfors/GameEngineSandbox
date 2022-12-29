#pragma once
#include "IInputManager.h"
#include <array>
#include <queue>

namespace Engine
{
  class InputManager : public IInputManager
  {
  public:
    InputManager() {}
    void AddKeyboardEvent(int keyCode, bool isPressed) override;
    void AddMouseEvent(MouseButton button, MouseButtonState state, int x, int y) override;
    bool IsKeyDown(int keyCode) override;
    MouseState GetMouseState() override;
    void Update();

  private:
    std::array<bool, 256> mKeyboard = {};
    std::queue<MouseState> mMouseStates = {};
  };
}
