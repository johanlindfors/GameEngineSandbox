#pragma once
#include <string>

namespace Utilities
{
    std::wstring s2ws(const std::string &str);
    std::string ws2s(const std::wstring &wstr);
}