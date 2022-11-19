#include "File.h"
#include <locale>
#include <codecvt>

using namespace std;
using namespace Engine;

using convert_type = std::codecvt_utf8<wchar_t>;

void File::Open(wstring filename)
{
    std::wstring_convert<convert_type, wchar_t> converter;
    std::string sFilename = converter.to_bytes(filename);
    mFileHandle= fopen(sFilename.c_str(), "rb");
}

void File::Close() {
    if(mFileHandle)  {
        auto err = fclose(mFileHandle);
        if(err != 0) {
            mFileHandle = nullptr;
        }
    }
}
