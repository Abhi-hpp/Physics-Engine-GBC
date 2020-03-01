#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct FireworksComponent
	{
		FireworksComponent(int _numberOfParticles = 6, int _generation = 3, float _spawnTime = 3, float _velocityScale = 10.0f, Color _color = Color::Green)
			:numberOfParticles(_numberOfParticles), generation(_generation), spawnTime(_spawnTime), velocityScale(_velocityScale),color(_color), timer(0.0f)
		{

		}
		int numberOfParticles;
		int generation;
		float spawnTime;
		float timer;
		float velocityScale;
		Color color;
	};
}
