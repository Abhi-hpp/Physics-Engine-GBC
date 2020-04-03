#pragma once
#include "ECSConfig.h"
namespace Reality
{
	struct ParticleSpawnerComponent
	{
		ParticleSpawnerComponent(unsigned int _numParticles = 10, float _duration = 1, float _particleSpeed = 10)
			:numberOfParticles(_numParticles), duration(_duration), particleSpeed(_particleSpeed), timer(_duration){}
		float particleSpeed;
		unsigned int numberOfParticles;
		float duration;
		float timer;
	};
}