#pragma once
#include "IHttpClient.hpp"

namespace Engine
{
    class CurlHttpClient : public IHttpClient
    {
        public:
            std::string get(std::string url) override;
    };
}