#pragma once
#include <memory>
#include <string>

namespace Engine {
	class Model;

	class ModelLoader {
	public:
		ModelLoader() = default;
		~ModelLoader() = default;

		std::shared_ptr<Engine::Model> loadModel(const std::string& fileName);
	};
}
