#pragma once
#include "Singleton.hpp"
#include <map>
#include <string>
#include <stdexcept>
#include <memory>

namespace Utilities
{
    class IOCContainer final : public Singleton<IOCContainer>
    {
    public:
        template <class T>
        static std::shared_ptr<T> resolve_type()
        {
            return instance().resolve<T>();
        }

        template <class T>
        static std::shared_ptr<T> resolve_type(std::string id)
        {
            return instance().resolve<T>(id);
        }

        template <class T>
        void register_type(std::shared_ptr<T> t)
        {
            const auto id = typeid(T).name();

            register_type_internal<T>(t, id);
        }

        template <class T>
        void register_type(std::shared_ptr<T> t, std::string differentiator)
        {
            const auto name = std::string(typeid(T).name());
            const auto id = std::string(name + "::" + differentiator);

            register_type_internal<T>(t, id);
        }

        template <class T>
        std::shared_ptr<T> resolve()
        {
            const auto id = typeid(T).name();

            return resolve_internal<T>(id);
        }

        template <class T>
        std::shared_ptr<T> resolve(std::string differentiator)
        {
            const auto name = std::string(typeid(T).name());
            const auto id = std::string(name + "::" + differentiator);

            return resolve_internal<T>(id);
        }

        template <class T>
        bool contains()
        {
            const auto id = std::string(typeid(T).name());

            return contains_internal<T>(id);
        }

        template <class T>
        bool contains(std::string differentiator)
        {
            const auto name = std::string(typeid(T).name());
            const auto id = std::string(name + "::" + differentiator);

            return contains_internal<T>(id);
        }

        template <class T>
        void remove()
        {
            const auto id = typeid(T).name();

            remove_internal<T>(id);
        }

        template <class T>
        void remove(std::string differentiator)
        {
            const auto name = std::string(typeid(T).name());
            const auto id = std::string(name + "::" + differentiator);

            remove_internal<T>(id);
        }

    private:
        template <class T>
        void register_type_internal(std::shared_ptr<T> t, std::string id)
        {
            const std::map<std::string, std::shared_ptr<void>>::iterator iter = _map.find(id);
            if (iter == _map.end())
            {
                _map[id] = t;
            }
        }

        template <class T>
        std::shared_ptr<T> resolve_internal(std::string id)
        {
            const std::map<std::string, std::shared_ptr<void>>::iterator iter = _map.find(id);
            if (iter != _map.end())
            {
                return std::static_pointer_cast<T>(iter->second);
            }
            char message[255];
            snprintf(message, sizeof(message), "Could not locate type in IOC: %s", id.c_str());
            throw std::runtime_error(message);
        }

        template <class T>
        bool contains_internal(std::string id)
        {
            const std::map<std::string, std::shared_ptr<void>>::iterator iter = _map.find(id);
            return iter != _map.end();
        }

        template <class T>
        void remove_internal(std::string id)
        {
            _map.erase(id);
        }

        std::map<std::string, std::shared_ptr<void>> _map;
    };
}
