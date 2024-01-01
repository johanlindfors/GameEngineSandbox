#include "filesystem/File.hpp"
#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>
#include "utilities/StringHelpers.hpp"
#include "utilities/Logger.hpp"

using namespace std;
using namespace Engine;

void File::open(string filename, bool writeable)
{
    mFilename = filename;
    debuglog << "[File::Open] Opening file '" << mFilename << "'!" << endl;
    mFileHandle = fopen(mFilename.c_str(), writeable ? "wb" : "rb");
    if(!mFileHandle) {
        debuglog << "Failed to open file!" << endl;
    }
}

void File::create(string filename)
{
    mFilename = filename;
    debuglog << "[File::Create] Creating file '" << mFilename << "'!" << endl;
    mFileHandle = fopen(mFilename.c_str(), "wb");
    if(!mFileHandle) {
        debuglog << "Failed to create file!" << endl;
    }
}

void File::close()
{
    if (mFileHandle)
    {
        const auto err = fclose(mFileHandle);
        if (err != 0)
        {
            mFileHandle = nullptr;
        }
    }
}

string File::readAllText()
{
    ifstream fileStream;
    fileStream.open(mFilename);
    stringstream buffer;
    buffer << fileStream.rdbuf();
    return buffer.str();
}
