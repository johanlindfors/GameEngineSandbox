#include "input/InputManager.h"
#include <cstdio>
using namespace Engine;

void InputManager::addKeyboardEvent(int keyCode, bool isPressed) 
{
	if(keyCode >=0 && keyCode < 256){
        if (mKeyboard[keyCode] != isPressed) {
            mKeyboard[keyCode] = isPressed;
        }
    }
}

void InputManager::AddMouseEvent(MouseButton button, MouseButtonState state, int x, int y) 
{
    MouseState newState;
    newState.Button = button;
    newState.State = state;
    newState.Position = Utilities::Point<int>(x, y);
    mMouseStates.push(newState);
}
    
bool InputManager::isKeyDown(int keyCode)
{
    if(keyCode >=0 && keyCode < 256){
        return mKeyboard[keyCode];
    }
    return false;
}

MouseState InputManager::GetMouseState() 
{
    MouseState result;
    if(mMouseStates.empty()) {
        result.State = MouseButtonState::None;
    } else {
        result = mMouseStates.front();        
    }
    return result;
}

void InputManager::Update() 
{
    if(!mMouseStates.empty()) {
        mMouseStates.pop();
    }
}