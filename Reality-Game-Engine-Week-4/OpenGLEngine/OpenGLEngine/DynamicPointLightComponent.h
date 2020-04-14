#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct DynamicPointLightComponent
	{
		DynamicPointLightComponent(float _radius = 1, Color _ambient = Color(), Color _diffuse = Color(), Color _specular = Color())
			: radius(_radius), ambient(_ambient), diffuse(_diffuse), specular(_specular) {}
		float radius;
		Color ambient;
		Color diffuse;
		Color specular;
	};
}
