#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct BuoyancyComponent
	{
		BuoyancyComponent(ECSEntity _target = ECSEntity(), Vector3 _localOffset = Vector3(0, 0, 0), const std::vector<int>& _horizontalKeys = {}, float _componentLength = 6,
			float _waterHeight = 0.0f, float _liquidDenisty = 10.0f, Vector3 _netForce = Vector3(0, 0, 0))
			:
			target(_target),
			offset(_localOffset),
			componentLength(_componentLength),
			waterHeight(_waterHeight),
			liquidDensity(_liquidDenisty),
			currentDensity(_liquidDenisty),
			HorizontalKeys(_horizontalKeys) {
		}

		ECSEntity target;
		float componentLength;
		float liquidDensity;
		float currentDensity;
		float waterHeight;
		Vector3 offset;
		Vector3 netForce;
		std::vector<int> HorizontalKeys;
	};
}
