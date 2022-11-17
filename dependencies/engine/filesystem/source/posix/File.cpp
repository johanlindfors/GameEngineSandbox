#include "File.h"
#include <cstdio>
#include <iostream>
#include "StringHelpers.h"

using namespace std;
using namespace Engine;
using namespace Utilities;

void File::Open(wstring filename)
{
    auto sFilename = ws2s(filename);
    std::cout << "[File::Open] Loading file '" << sFilename << "'!" << endl;
    mFileHandle = fopen(sFilename.c_str(), "rb");
    if(!mFileHandle) {
        std::cout << "Failed to open file!" << endl;
    }
}

void File::Close() {
    if(mFileHandle)  {
	    const auto err = fclose(mFileHandle);
        if(err != 0) {
            mFileHandle = nullptr;
        }
    }
}