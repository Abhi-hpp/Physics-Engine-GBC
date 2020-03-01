#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct ParticleCollideCheck
	{
		ParticleCollideCheck(ECSEntity _entityA = ECSEntity(), ECSEntity _entityB = ECSEntity(), float _restitution = 1.0f,	Vector3 _normal = Vector3(0, 1.0f, 0), float _penetration = 0.0f)
			: entityA(_entityA), entityB(_entityB),	restitution(_restitution), normal(_normal),	penetration(_penetration)
		{

		}


		ECSEntity entityA;
		ECSEntity entityB;
		Vector3 normal;


		float penetration;
		float restitution;
		
		
	};
}
