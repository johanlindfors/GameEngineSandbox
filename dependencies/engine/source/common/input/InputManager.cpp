#include "input/InputManager.h"

using namespace Engine;

void InputManager::AddKeyboardEvent(int keyCode, bool isPressed) 
{
	if(keyCode >=0 && keyCode < 256){
        if (mKeyboard[keyCode] != isPressed) {
            mKeyboard[keyCode] = isPressed;
        }
    }
}
    
bool InputManager::IsKeyDown(int keyCode)
{
    if(keyCode >=0 && keyCode < 256){
        return mKeyboard[keyCode];
    }
    return false;
}
