#include "physics/PhysicsEngine.h"
#include "physics/IPhysicsBody.h"
#include "utilities/IStepTimer.h"

using namespace std;
using namespace Engine;
using namespace Utilities;

#define GRAVITY 9.1f

void PhysicsEngine::AddBody(shared_ptr<IPhysicsBody> body)
{
	mBodies.push_back(body);
}

void PhysicsEngine::Update(shared_ptr<IStepTimer> timer)
{
	for (auto body : mBodies)
	{
		if(!body->IsAlive) continue;
		
		auto velocity = body->Velocity;
		if (body->AllowGravity)
		{
			velocity.m[1] = velocity.m[1] - (GRAVITY * timer->GetElapsedMilliSeconds() / 9.0f);
		}

		body->Position.X += (velocity.m[0] * timer->GetElapsedMilliSeconds() / 1000.0f);
		body->Position.Y += (velocity.m[1] * timer->GetElapsedMilliSeconds() / 1000.0f);
		body->Velocity = velocity;
	}	
}
