#include "filesystem/FileSystem.h"
#include <Windows.h>

using namespace Engine;

std::wstring FileSystem::GetResourcesDirectory()
{
	if (IsDebuggerPresent()) 
	{
#if _DEBUG
		return L"\\Debug\\resources\\";
#else
		return L"\\Release\\resources\\";
#endif
	} 
	else
	{
		return L"\\resources\\";
	}
}