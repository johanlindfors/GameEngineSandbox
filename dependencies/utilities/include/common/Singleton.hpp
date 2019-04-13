#pragma once
#include <memory>

template<typename T>
class Singleton {
public:
    static T& Instance()
    {        
        static T instance{};
        return instance;
    }
    Singleton(const Singleton&) = delete;
    Singleton& operator= (const Singleton) = delete;

protected:
    Singleton() {}
};
