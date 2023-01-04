#pragma once
#include "IPhysicsEngine.h"
#include <vector>

namespace Engine {
	class IPhysicsBody;

	class PhysicsEngine : public IPhysicsEngine {
	public:
		PhysicsEngine() 
			: mBodies(std::vector<std::shared_ptr<IPhysicsBody>>())
			, mIsActive(true) { }

		~PhysicsEngine() = default;

		// Engine::IPhysicsEngine 
		void addBody(std::shared_ptr<IPhysicsBody> body) override;
		void update(std::shared_ptr<Utilities::IStepTimer> timer) override;

	private:
		std::vector<std::shared_ptr<IPhysicsBody>> mBodies;
		bool mIsActive;
	};
}
