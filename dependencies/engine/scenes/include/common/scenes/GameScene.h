#pragma once
#include <memory>
#include <string>

namespace Engine {
	class IRenderer;
}
namespace Utilities {
	class IStepTimer;
}

namespace Engine {
	
	class GameScene {
	public:
		virtual ~GameScene() = default;
		std::string id;
		virtual void load() = 0;
		virtual void unload() = 0;
		virtual void updateScreenSize(int width, int height) = 0;
		virtual void update(std::shared_ptr<Utilities::IStepTimer> timer) = 0;
		virtual void draw(std::shared_ptr<Engine::IRenderer> renderer) = 0;
	};
}