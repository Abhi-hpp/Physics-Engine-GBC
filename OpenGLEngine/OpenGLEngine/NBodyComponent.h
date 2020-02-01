#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct NBodyComponent
	{
		int numberOfParticles;
		int generation;
		float spawnTime;
		float lifeSpan;
		float timer;
		float velocityScale;

		NBodyComponent(int _numberOfParticles = 6, int _generation = 1, float _spawnTime = 3, float _lifeSpan = 10, float _velocityScale = 1.0f)
			: numberOfParticles(_numberOfParticles), generation(_generation), spawnTime(_spawnTime), lifeSpan(_lifeSpan), velocityScale(_velocityScale), timer(0.0f)
		{}
	};
}
