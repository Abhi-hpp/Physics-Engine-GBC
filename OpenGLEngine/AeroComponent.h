#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct AeroComponent
	{
		AeroComponent(ECSEntity _target = ECSEntity(), Mat3 _aerodynamicTensor = Mat3(1.0f), Vector3 _relativePoint = Vector3(0, 0, 0))
			:target(_target), aerodynamicTensor(_aerodynamicTensor), relativePoint(_relativePoint)
		{

		}
		Mat3 aerodynamicTensor;
		ECSEntity target;
		Vector3 relativePoint;
	};
}
