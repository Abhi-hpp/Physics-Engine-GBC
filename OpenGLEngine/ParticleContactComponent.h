#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct ParticleContactComponent
	{
		ParticleContactComponent(ECSEntity a = ECSEntity(), 
			ECSEntity b = ECSEntity(), 
			float _restitution = 1, 
			Vector3 _normal = Vector3(0,1,0), float _penetration = 0):
			entityA(a),
			entityB(b),
			restitution(_restitution),
			normal(_normal),
			penetration (_penetration),
			deltaMovePerMass(Vector3(0, 0, 0)){}
		ECSEntity entityA;
		ECSEntity entityB;
		float restitution;
		Vector3 normal;
		float penetration;
		Vector3 deltaMovePerMass;
	};
}