#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct BuoyancyComponent
	{
		BuoyancyComponent(ECSEntity _targetEntity = ECSEntity(), Vector3 _localOffset = Vector3(0, 0, 0), Vector3 _dimensions = Vector3(1.0, 1.0, 1.0),
			float _waterHeight = 0.0f, float _liquidDenisty = 5000, const std::vector<int>& _horizontalKeys = {})
			:
			targetEntity(_targetEntity),
			localOffset(_localOffset),
			dimensions(_dimensions),
			waterHeight(_waterHeight),
			liquidDensity(_liquidDenisty),
			currentDensity(_liquidDenisty),
			HorizontalKeys(_horizontalKeys)
		{

		}

		// using this to allow for custom dimensions of the buuoyancy component
		ECSEntity targetEntity;
		Vector3 dimensions;
		float waterHeight;
		float liquidDensity;
		float currentDensity;
		Vector3 localOffset;
		Vector3 netForce = Vector3(0, 0, 0);

		std::vector<int> HorizontalKeys;
	};
}
