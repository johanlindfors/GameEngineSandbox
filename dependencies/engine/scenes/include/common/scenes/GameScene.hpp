#pragma once
#include <memory>
#include <string>

namespace Engine
{
	class IRenderer;
}
namespace Utilities
{
	class IStepTimer;
}

namespace Engine
{

	class GameScene
	{
	public:
		virtual ~GameScene() = default;
		std::string id;
		virtual void load(){};
		virtual void unload(){};
		virtual void updateScreenSize(int width, int height){};
		virtual void update(std::shared_ptr<Utilities::IStepTimer> timer){};
		virtual void draw(std::shared_ptr<Engine::IRenderer> renderer){};
	};
}