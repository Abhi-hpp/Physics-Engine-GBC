#pragma once
#include "ECSConfig.h"
#include "ParticleContactComponent.h"

namespace Reality
{
	class ParticleContactResolutionSystem : public ECSSystem
	{
	public:
		ParticleContactResolutionSystem();
		void Update(float deltaTime);
		unsigned int iterations = 1;
	private:
		float CalculateSeparatingVelocity(ParticleContactComponent& contact);
		void ResolveVelocity(ParticleContactComponent& contact, float deltaTime);
		void ResolveInterpenetration(ParticleContactComponent& contact);
		void UpdateInterpenetration(ParticleContactComponent& bestContact, ParticleContactComponent& contact);
		unsigned int iterationsUsed = 0;
	};
}

