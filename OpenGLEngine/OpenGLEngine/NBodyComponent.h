#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct NBodyComponent
	{
		NBodyComponent(float _mass = 1.0f, float _gravity = 1.0f, vector<ECSEntity> _entities = vector<ECSEntity>())
			: mass(_mass), gravity(_gravity), entities(_entities)
		{

		}
		vector<ECSEntity> entities;

		float mass;
		float gravity;
	};
}
