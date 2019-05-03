#include "filesystem/File.h"

using namespace std;
using namespace winrt;
using namespace Windows::Storage;
using namespace Engine;

void File::Open(wstring filename)
{
    mStorageFile = StorageFile::GetFileFromPathAsync(filename).get();
}

void File::Close() 
{
    if(mStorageFile) {
        mStorageFile = nullptr;
    }
}