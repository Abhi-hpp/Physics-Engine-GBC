#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct ParticleContactEvent
	{
		ParticleContactEvent(ECSEntity _entityA = ECSEntity(), ECSEntity _entityB = ECSEntity(), 
			float _restitution = 1.f, Vector3 _normal = Vector3(0, 1, 0), float _penetration = 0)
			: entityA(_entityA), entityB(_entityB), restitution(_restitution), normal(_normal), penetration(_penetration)
		{

		}
		ECSEntity entityA;
		ECSEntity entityB;
		float restitution;
		Vector3 normal;
		float penetration;
	};
}
