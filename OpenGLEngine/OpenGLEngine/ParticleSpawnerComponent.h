#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct ParticleSpawnerComponent
	{
		ParticleSpawnerComponent(int _numberOfParticles = 10, float _spawnTime = 3) :
			numberOfParticles(_numberOfParticles), spawnTime(_spawnTime), timer(0)
		{

		}

		int numberOfParticles;
		float timer;
		float spawnTime;
	};
}
