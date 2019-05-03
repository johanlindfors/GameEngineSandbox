#include "filesystem/File.h"

using namespace std;
using namespace winrt;
using namespace Windows::Storage;
using namespace Engine;

void File::Load(wstring filename)
{
    mStorageFile = StorageFile::GetFileFromPathAsync(filename).get();
}