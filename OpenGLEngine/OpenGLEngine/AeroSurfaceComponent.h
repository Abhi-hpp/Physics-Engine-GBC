#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct AeroSurfaceComponent
	{
		AeroSurfaceComponent(ECSEntity _targetEntity = ECSEntity(), Mat3 _aerodynamicTensor = Mat3(0.1f),
			Vector3 _localOffset = Vector3(0, 0, 0))
			:targetEntity(_targetEntity),
			aerodynamicTensor(_aerodynamicTensor),
			localOffset(_localOffset)
		{

		}
		ECSEntity targetEntity;
		Mat3 aerodynamicTensor;
		Vector3 localOffset;
	};
}
