#include "filesystem/File.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include "utilities/StringHelpers.hpp"
#include "utilities/Logger.hpp"

using namespace std;
using namespace Engine;
using namespace Utilities;

void File::open(string filename, bool writeable)
{
    auto wFilename = s2ws(filename);
    const auto err = _wfopen_s(&mFileHandle, wFilename.c_str(), writeable ? L"wb" : L"rb");
    if (err != 0)
    {
        mFileHandle = nullptr;
    }
}

void File::create(string filename)
{
    auto wFilename = s2ws(filename);
    debuglog << "[File::Create] Creating file '" << filename << "'!" << endl;
    _wfopen_s(&mFileHandle, wFilename.c_str(), L"wb");
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