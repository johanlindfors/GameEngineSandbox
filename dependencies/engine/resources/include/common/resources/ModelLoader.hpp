#pragma once
#include <memory>
#include <string>
#include "resources/Model.hpp"

namespace Engine
{
	class ModelLoader
	{
	public:
		ModelLoader() = default;
		~ModelLoader() = default;

		std::shared_ptr<Engine::ModelBase> loadModel(const std::string &fileName);
	};
}
