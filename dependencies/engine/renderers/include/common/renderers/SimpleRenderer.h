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
			, mWidth(0)
			, mHeight(0)
			, VBO(0)
			, cubeVAO(0)
			, lightCubeVAO(0)
			{ }
			
		~SimpleRenderer() = default;

		// Engine::IRenderer
        void initialize() override;
		void updateWindowSize(int width, int height) override;
		void clear() override;
		
		void draw();
		// void Draw(std::shared_ptr<Sprite> sprite, Utilities::Point<float> position) override;

	private:
		unsigned int VBO, cubeVAO;
		unsigned int lightCubeVAO;
		std::shared_ptr<Shader> lightingShader;
		std::shared_ptr<Shader> lightCubeShader;
		Camera camera;
		float angle;
		int mWidth, mHeight;
	};
}
