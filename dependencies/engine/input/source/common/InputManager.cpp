#include "input/InputManager.h"

using namespace Engine;

void InputManager::addKeyboardEvent(int keyCode, bool isPressed) 
{
	if(keyCode >=0 && keyCode < 256){
        if (mKeyboard[keyCode] != isPressed) {
            mKeyboard[keyCode] = isPressed;
        }
    }
}
    
bool InputManager::isKeyDown(int keyCode)
{
    if(keyCode >=0 && keyCode < 256){
        return mKeyboard[keyCode];
    }
    return false;
}
