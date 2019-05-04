#include "File.h"

using namespace std;
using namespace Engine;

void File::Open(wstring filename)
{
    auto err = _wfopen_s(&mFileHandle, filename.c_str(), L"rb");
    if ( err != 0) {
        mFileHandle = nullptr;
    }
}

void File::Close() {
    if(mFileHandle)  {
        auto err = fclose(mFileHandle);
        if(err != 0) {
            mFileHandle = nullptr;
        }
    }
}