#pragma once
#include <Singleton.hpp>
#include <map>
#include <string>

class IOCContainer final : public Singleton<IOCContainer> {
    public:
        template<class T>
        void Register(std::shared_ptr<T> t)
        {
            auto id = typeid(T).raw_name();

            std::map<std::string, std::shared_ptr<void>>::iterator iter = _map.find(id);
            if (iter == _map.end())
            {
                _map[id] = t;
            }
        }

        template<class T>
        std::shared_ptr<T> Resolve()
        {
            auto id = typeid(T).raw_name();

            std::map<std::string, std::shared_ptr<void>>::iterator iter = _map.find(id);
            if (iter != _map.end())
            {
                return std::static_pointer_cast<T>(iter->second);
            }
            throw std::runtime_error("Could not locate type in IOC");
        }

    private:
        std::map<std::string, std::shared_ptr<void>> _map;
};
