#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct NBodyComponent
	{
		NBodyComponent(float _mass = 1.0f, float _gravitationalConstant = 50.0f)
			: mass(_mass), gravitationalConstant(_gravitationalConstant)
		{

		}
		float mass;
		float gravitationalConstant;
	};
}
