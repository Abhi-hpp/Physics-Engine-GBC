#pragma once
#include "ECSConfig.h"
#include "Color.h"
namespace Reality
{
	struct DynamicDirectionalLightComponent
	{
		DynamicDirectionalLightComponent(Color _ambient = Color(), Color _diffuse = Color(), Color _specular = Color())
			: ambient(_ambient), diffuse(_diffuse), specular(_specular){}
		Color ambient;
		Color diffuse;
		Color specular;
	};
}