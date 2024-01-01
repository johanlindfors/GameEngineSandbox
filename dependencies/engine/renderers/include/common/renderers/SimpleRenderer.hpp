#pragma once
#include <memory>
#include "IRenderer.hpp"
#include "Camera.hpp"

namespace Engine
{
	class Shader;

	class SimpleRenderer : public IRenderer
	{
	public:
		SimpleRenderer()
			: camera(glm::vec3(0.0f, 0.0f, 5.0f))
			, angle(0.0f)
			, mWidth(0)
			, mHeight(0)
			, VBO(0)
			, cubeVAO(0)
			, lightCubeVAO(0)
		{
		}

		~SimpleRenderer() = default;

		// Engine::IRenderer
		void initialize() override;
		void updateWindowSize(int width, int height) override;
		void clear() override;
		void clear(float r, float g, float b, float a) override;

		void draw();

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
