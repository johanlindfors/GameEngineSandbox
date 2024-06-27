#pragma once
#include <memory>
#include <string>

namespace Engine
{
	class Model;

	class ObjModelLoader
	{
	public:
		ObjModelLoader() = default;
		~ObjModelLoader() = default;

		std::shared_ptr<Engine::Model> loadModel(const std::string &fileName);
	};
}
