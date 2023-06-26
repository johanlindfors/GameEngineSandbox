#include "filesystem/File.hpp"

#include "winrt/Windows.Foundation.hpp"

using namespace std;
using namespace winrt;
using namespace Windows::Storage;
using namespace Engine;

void File::open(string filename)
{
    std::replace(filename.begin(), filename.end(), '/', '\\');
    mStorageFile = StorageFile::GetFileFromPathAsync(filename).get();
}

void File::close()
{
    if(mStorageFile) {
        mStorageFile = nullptr;
    }
}