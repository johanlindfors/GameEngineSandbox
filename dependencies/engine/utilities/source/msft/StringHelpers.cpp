#include "utilities/StringHelpers.hpp"
#include <locale>
#include <Windows.h>

namespace Utilities {
    std::wstring s2ws(const std::string& str)
    {
        if (str.empty())
        {
            return L"";
        }

        const auto size_needed = MultiByteToWideChar(CP_UTF8, 0, &str.at(0), (int)str.size(), nullptr, 0);
        if (size_needed <= 0)
        {
            throw std::runtime_error("MultiByteToWideChar() failed: " + std::to_string(size_needed));
        }

        std::wstring result(size_needed, 0);
        MultiByteToWideChar(CP_UTF8, 0, &str.at(0), (int)str.size(), &result.at(0), size_needed);
        return result;
    }

    std::string ws2s(const std::wstring& wstr)
    {
        if (wstr.empty())
        {
            return "";
        }

        const auto size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr.at(0), (int)wstr.size(), nullptr, 0, nullptr, nullptr);
        if (size_needed <= 0)
        {
            throw std::runtime_error("WideCharToMultiByte() failed: " + std::to_string(size_needed));
        }

        std::string result(size_needed, 0);
        WideCharToMultiByte(CP_UTF8, 0, &wstr.at(0), (int)wstr.size(), &result.at(0), size_needed, nullptr, nullptr);
        return result;
    }
}