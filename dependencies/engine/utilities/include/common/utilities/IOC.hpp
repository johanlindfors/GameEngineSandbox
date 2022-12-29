#pragma once
#include "utilities/Singleton.h"
#include <map>
#include <string>
#include <stdexcept>
#include <memory>

namespace Utilities {
    class IOCContainer final : public Singleton<IOCContainer> {
        public:
            template<class T>
            void Register(std::shared_ptr<T> t)
            {
	            const auto id = typeid(T).name();

	            const std::map<std::string, std::shared_ptr<void>>::iterator iter = _map.find(id);
                if (iter == _map.end())
                {
                    _map[id] = t;
                }
            }

            template<class T>
            std::shared_ptr<T> Resolve()
            {
	            const auto id = typeid(T).name();

	            const std::map<std::string, std::shared_ptr<void>>::iterator iter = _map.find(id);
                if (iter != _map.end())
                {
                    return std::static_pointer_cast<T>(iter->second);
                }
                char message[255];
                sprintf(message, "Could not locate type in IOC: %s", id);
                throw std::runtime_error(message);
            }

            template<class T>
            bool Contains()
            {
	            const auto id = typeid(T).name();
	            const std::map<std::string, std::shared_ptr<void>>::iterator iter = _map.find(id);
                return iter != _map.end();
            }

            template<class T>
            void Remove() {
	            const auto id = typeid(T).name();

                _map.erase(id);
            }


        private:
            std::map<std::string, std::shared_ptr<void>> _map;
    };
}
