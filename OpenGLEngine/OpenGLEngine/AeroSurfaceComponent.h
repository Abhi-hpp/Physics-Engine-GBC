#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct AeroSurfaceComponent
	{
		AeroSurfaceComponent(ECSEntity _targetEntity = ECSEntity(), Vector3 _aerodynamicForce = Vector3(0, 0, 0),
			Vector3 _localOffset = Vector3(0, 0, 0), 
			float _liquidDensity = 1000.0f, 
			float _radius = 5.0f, 
			float _volume = 2.0f, 
			float _maxDepth = 15.0f, 
			float _waterHeight = 10.0f)
			:targetEntity(_targetEntity),
			aerodynamicForce(_aerodynamicForce),
			localOffset(_localOffset), 
			liquidDensity(_liquidDensity), 
			radius(_radius), 
			volume(_volume), 
			maxDepth(_maxDepth), 
			waterHeight(_waterHeight)
		{

		}
		ECSEntity targetEntity;
		Vector3 aerodynamicForce;
		Vector3 localOffset;

		float radius;
		float volume;
		float maxDepth;
		float waterHeight;
		float liquidDensity;
		Vector3 finalPos;
	};
}
