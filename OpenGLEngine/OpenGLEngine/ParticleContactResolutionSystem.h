#pragma once
#include "ECSConfig.h"
#include "ParticleContactEvent.h"

namespace Reality
{
	class ParticleContactResolutionSystem : public ECSSystem
	{
	public:
		ParticleContactResolutionSystem();
		void Update(float deltaTime);
	private:
		float CalculateSeparationVelocity(ParticleContactEvent& contact);
		float CalculateActualPenetration(ParticleContactEvent& contact);
		void ResolveVelocity(ParticleContactEvent& contact, float deltaTime);
		void ResolveInterPenetration(ParticleContactEvent& contact);
		int velocityIterations = 4;
		int positionIterations = 8;
	};
}
