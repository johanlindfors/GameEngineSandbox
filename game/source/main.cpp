#include <Windows.h>
#include <test.h>
#include <iostream>

int WinMain(HINSTANCE , HINSTANCE , LPSTR , int)
{
    Person p("Johan", "Lindfors");
    std::cout << p.GetName() << std::endl;	
    return 0;
}