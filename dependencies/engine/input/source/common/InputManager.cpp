#include "input/InputManager.h"
#include <cstdio>
using namespace Engine;

void InputManager::addKeyboardEvent(int keyCode, bool isPressed) 
{
	if(keyCode >=0 && keyCode < 256){
        mKeyboard[keyCode] = isPressed;        
    }
}

void InputManager::addMouseEvent(MouseButton button, MouseButtonState state, int x, int y) 
{
    MouseState newState;
    newState.button = button;
    newState.state = state;
    newState.position = Utilities::Point<int>{x, y};
    mMouseStates.push(newState);
}
    
bool InputManager::isKeyDown(int keyCode)
{
    if(keyCode >=0 && keyCode < 256){
        return mKeyboard[keyCode];
    }
    return false;
}

MouseState InputManager::getMouseState() 
{
    MouseState result;
    if(mMouseStates.empty()) {
        result.state = MouseButtonState::None;
    } else {
        result = mMouseStates.front();        
    }
    return result;
}

void InputManager::update() 
{
    if(!mMouseStates.empty()) {
        mMouseStates.pop();
    }
}