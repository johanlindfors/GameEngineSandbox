#include "filesystem/File.h"

using namespace std;

void Engine::File::Load(wstring filename)
{
    auto err = _wfopen_s(&mFileHandle, filename.c_str(), L"rb");
    if ( err != 0) {
        mFileHandle = nullptr;
    }
}