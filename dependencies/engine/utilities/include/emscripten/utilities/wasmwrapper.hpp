#include <emscripten.h>
#include <emscripten/val.h>
#include <string>

static std::string getCurrentUrl() {
    emscripten::val location = emscripten::val::global("location");
    // auto port = location["port"].as<std::string>();
    // auto protocol = location["protocol"].as<std::string>();
    // auto hostname = location["hostname"].as<std::string>();

    return location["href"].as<std::string>();
}
