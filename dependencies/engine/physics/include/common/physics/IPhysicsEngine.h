#pragma once
#include <memory>

namespace Utilities
{
	class IStepTimer;
}

namespace Engine {

	class IPhysicsBody;

	class IPhysicsEngine {
	public:
		virtual void AddBody(std::shared_ptr<IPhysicsBody> body) = 0;
		virtual void Update(std::shared_ptr<Utilities::IStepTimer> timer) = 0;
	};
}
