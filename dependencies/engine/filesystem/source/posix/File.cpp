#include "File.h"
#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>
#include "utilities/StringHelpers.h"

using namespace std;
using namespace Engine;
using namespace Utilities;

void File::Open(string filename, bool writeable)
{
    mFilename = filename;
    std::cout << "[File::Open] Opening file '" << mFilename << "'!" << endl;
    mFileHandle = fopen(mFilename.c_str(), writeable ? "wb" : "rb");
    if(!mFileHandle) {
        std::cout << "Failed to open file!" << endl;
    }
}

void File::Create(string filename) 
{
    mFilename = filename;
    std::cout << "[File::Create] Creating file '" << mFilename << "'!" << endl;
    mFileHandle = fopen(mFilename.c_str(), "wb");
    if(!mFileHandle) {
        std::cout << "Failed to create file!" << endl;
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

string File::ReadAllText() {
    ifstream fileStream;
    fileStream.open(mFilename);
    stringstream buffer;
    buffer << fileStream.rdbuf();
    return buffer.str();
}
