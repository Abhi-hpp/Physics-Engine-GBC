#pragma once
#include "ECSConfig.h"
#include "ParticleCollideCheck.h"

namespace Reality
{
	class ParticleCollisionResolvingSystem : public ECSSystem
	{
	public:
		ParticleCollisionResolvingSystem();
		void Update(float deltaTime);
	private:

		int velocityIncrements = 2;
		int positionIncrements = 4;

		//Functions
		float BounceOffVelocity(ParticleCollideCheck& collide);
		float CheckPenetration(ParticleCollideCheck& collide);
		void SolveVelocity(ParticleCollideCheck& collide, float deltaTime);
		void ResolveBounceOnPenetration(ParticleCollideCheck& collide);
	
	};
}
