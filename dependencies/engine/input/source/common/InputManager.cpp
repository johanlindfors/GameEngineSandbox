#include "input/InputManager.hpp"
#include <cstdio>
#include <iostream>

using namespace Engine;

void InputManager::addKeyboardEvent(int keyCode, ButtonState state)
{
    if (keyCode >= 0 && keyCode < 256)
    {
        mKeyboard[keyCode] = state;
    }
}

void InputManager::addMouseEvent(MouseButton button, ButtonState state, int x, int y)
{
    MouseState newState;
    newState.button = button;
    newState.state = state;
    newState.position = Utilities::Point<int>{x, y};
    mMouseStates.push(newState);
}

bool InputManager::isKeyDown(int keyCode)
{
    if (keyCode >= 0 && keyCode < 256)
    {
        return mKeyboard[keyCode] == ButtonState::Pressed ||
               mKeyboard[keyCode] == ButtonState::Repeat;
    }
    return false;
}

MouseState InputManager::getMouseState()
{
    MouseState result;
    if (mMouseStates.empty())
    {
        result.state = ButtonState::None;
    }
    else
    {
        result = mMouseStates.front();
    }
    return result;
}

void InputManager::update()
{
    if (!mMouseStates.empty())
    {
        mMouseStates.pop();
    }
}