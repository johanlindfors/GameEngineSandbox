#pragma once
#include <memory>

namespace Engine
{
	class IStepTimer;
}

namespace Engine
{

	struct IPhysicsBody;

	class IPhysicsEngine
	{
	public:
		virtual void addBody(std::shared_ptr<IPhysicsBody> body) = 0;
		virtual void update(std::shared_ptr<Engine::IStepTimer> timer) = 0;
	};
}
