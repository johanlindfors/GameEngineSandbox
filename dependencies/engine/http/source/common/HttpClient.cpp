#include "http/HttpClient.hpp"
#include <cpr/cpr.h>

using namespace std;
using namespace Engine;

string HttpClient::get(string url) 
{
    cpr::Response r = cpr::Get(cpr::Url{url});
    return r.text;
}