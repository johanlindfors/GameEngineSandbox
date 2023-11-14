#pragma once
#include <string>

namespace Engine
{
    class IHttpClient
    {
    public:
        virtual std::string get(std::string url) = 0;
    };
}
