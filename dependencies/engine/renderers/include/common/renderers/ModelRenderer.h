#pragma once
#include <memory>
#include "Renderer.h"
#include "utilities/GLHelper.h"
#include "utilities/MathHelper.h"
#include <glm/glm.hpp>

namespace Engine 
{
    class Shader;
    class Camera;
    struct Sprite;
    class Model;

    class ModelRenderer : public Renderer {
        public:
            ModelRenderer(std::shared_ptr<Engine::Shader> shader, std::shared_ptr<Engine::Camera> camera);
            ~ModelRenderer();
            virtual void initialize() override;
            virtual void updateWindowSize(int width, int height) override;
		    virtual void clear() override;
            virtual void clear(float r, float g, float b, float a) override;

            void drawModel(std::shared_ptr<Engine::Model> model, glm::mat4 &world);

        private:
            std::shared_ptr<Engine::Camera> mCamera;
    };
}
