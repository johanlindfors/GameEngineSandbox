#include "utilities/StringHelpers.hpp"
#include <locale>
#include <codecvt>

namespace Utilities {
    std::wstring s2ws(const std::string& str)
    {
        using convert_typex = std::codecvt_utf8<wchar_t>;
        std::wstring_convert<convert_typex, wchar_t> converterX;
        return converterX.from_bytes(str);
    }

    std::string ws2s(const std::wstring& wstr)
    {
        using convert_typex = std::codecvt_utf8<wchar_t>;
        std::wstring_convert<convert_typex, wchar_t> converterX;
        return converterX.to_bytes(wstr);
    }
}