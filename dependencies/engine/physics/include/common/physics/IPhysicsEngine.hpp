#pragma once
#include <memory>

namespace Utilities
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
		virtual void update(std::shared_ptr<Utilities::IStepTimer> timer) = 0;
	};
}
