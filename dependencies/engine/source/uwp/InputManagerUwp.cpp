#include "input/InputManager.h"

void InputManager::AddKeyboardEvent(int keyCode, bool isPressed) 
{
    mKeyboardEvents.push_back(KeyboardEvent(keyCode, isPressed));
}
    
bool InputManager::IsKeyDown(int keyCode)
{
    for(auto const& keyboardEvent : mKeyboardEvents) {
        if(keyboardEvent.mKeyCode == keyCode && keyboardEvent.mIsPressed){
            return true;
        }
    }
    return false;
}

void InputManager::ProcessEvents()
{
    mKeyboardEvents.clear();
}