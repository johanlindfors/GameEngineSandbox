#pragma once
#include <memory>
#include <string>
#include "resources/Model.hpp"

namespace Engine
{
	//class Model;

	class ObjModelLoader
	{
	public:
		ObjModelLoader() = default;
		~ObjModelLoader() = default;

		std::shared_ptr<Engine::ModelBase> loadModel(const std::string &fileName);
	};
}
