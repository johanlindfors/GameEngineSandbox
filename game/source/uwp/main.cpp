#include <Windows.h>
#include <test.h>
#include <iostream>

void StartUwpApplication();

int __stdcall wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
{
	StartUwpApplication();
    //Person p("Johan", "Lindfors");
    //std::cout << p.GetName() << std::endl;	
    return 0;
}