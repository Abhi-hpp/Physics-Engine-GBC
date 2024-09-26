#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct DynamicSpotLightComponent
	{
		DynamicSpotLightComponent(float _angle = 45, float _range = 10, Color _ambient = Color(), Color _diffuse = Color(), Color _specular = Color(), float _fallOffAngle = 10)
			: angle(_angle), range(_range), ambient(_ambient), diffuse(_diffuse), specular(_specular), fallOffAngle(_fallOffAngle) {}
		float angle;
		float range;
		Color ambient;
		Color diffuse;
		Color specular;
		float fallOffAngle;
	};
}
