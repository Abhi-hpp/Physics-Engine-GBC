#pragma once
#include "ECSConfig.h"
#include "TransformComponent.h"
#include "RotateComponent.h"

using namespace Reality;
class RotateSystem : public ECSSystem
{
public:
	RotateSystem();
	void Update(float deltaTime);
};

