#pragma once
#include "IHttpClient.hpp"

namespace Engine
{
    class HttpClient : public IHttpClient
    {
        public:
            std::string get(std::string url) override;
    };
}