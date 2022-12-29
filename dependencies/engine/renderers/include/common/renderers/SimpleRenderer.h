#pragma once
#include <memory>
#include "IRenderer.h"
#include "Camera.hpp"

namespace Engine {
	class Shader;

	class SimpleRenderer : public IRenderer {
	public:
		SimpleRenderer() 
			: camera(glm::vec3(0.0f, 0.0f, 5.0f))
			, angle(0.0f)
			{ }
		~SimpleRenderer() = default;

		// Engine::IRenderer
        void Initialize() override;
		void UpdateWindowSize(int width, int height) override;
		void Clear() override;
		
		void Draw();
		// void Draw(std::shared_ptr<Sprite> sprite, Utilities::Point<float> position) override;

	private:
		unsigned int VBO, cubeVAO;
		unsigned int lightCubeVAO;
		std::shared_ptr<Shader> lightingShader;
		std::shared_ptr<Shader> lightCubeShader;
		Camera camera;
		float angle;
	};
}
