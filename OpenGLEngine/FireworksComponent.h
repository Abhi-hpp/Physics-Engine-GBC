#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct FireworksComponent
	{
		FireworksComponent(int _numParticles = 6, int _generation = 3, float _spawnTime = 3.0f, float _velocityScale = 10.0f)
			: numParticles(_numParticles), generation(_generation), spawnTime(_spawnTime), velocityScale(_velocityScale), timer(0.0f)
		{

		}
		int numParticles;
		int generation;
		float spawnTime;
		float timer;
		float velocityScale;
	};
}
