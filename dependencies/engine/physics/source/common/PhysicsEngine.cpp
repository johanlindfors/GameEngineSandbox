#include "physics/PhysicsEngine.hpp"
#include "physics/IPhysicsBody.hpp"
#include "utilities/IStepTimer.hpp"

using namespace std;
using namespace Engine;
using namespace Engine;

#define GRAVITY 9.1f

void PhysicsEngine::addBody(shared_ptr<IPhysicsBody> body)
{
	mBodies.push_back(body);
}

void PhysicsEngine::update(shared_ptr<IStepTimer> timer)
{
	for (auto body : mBodies)
	{
		if (!body->isAlive)
			continue;

		auto velocity = body->velocity;
		if (body->allowGravity)
		{
			velocity.idx[1] = velocity.y - (GRAVITY * timer->getElapsedMilliSeconds() / 9.0f);
		}

		body->position.x += (velocity.x * timer->getElapsedMilliSeconds() / 1000.0f);
		body->position.y += (velocity.y * timer->getElapsedMilliSeconds() / 1000.0f);
		body->velocity = velocity;
	}
}
