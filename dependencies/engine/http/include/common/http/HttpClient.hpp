#pragma once
#include "IHttpClient.hpp"

namespace Engine
{
    class CprHttpClient : public IHttpClient
    {
    public:
        std::string get(std::string url) override;
    };

    class CurlHttpClient : public IHttpClient
    {
    public:
        std::string get(std::string url) override;
    };
}
