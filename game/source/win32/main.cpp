#include <Windows.h>
#include <test.h>
#include <iostream>

void StartWin32Application();

int __stdcall wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
{
	StartWin32Application();
    //Person p("Johan", "Lindfors");
    //std::cout << p.GetName() << std::endl;	
    return 0;
}