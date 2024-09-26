#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct FireworksComponent
	{
		FireworksComponent(int _numberOfParticles = 6, int _generation = 3, float _spawnTime = 1.5f, float _velocityScale = 10.0f) :
			numberOfParticles(_numberOfParticles), generation(_generation), spawnTime(_spawnTime), velocityScale(_velocityScale), timer(0.0f)
		{

		}

		int numberOfParticles;
		int generation;
		float spawnTime;
		float timer;
		float velocityScale;
	};
}
