#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct AeroControlComponent
	{
		AeroControlComponent(Vector3 _aeroPlusOne = Vector3(0, 0, 0), Vector3 _aeroMinusOne = Vector3(0, 0, 0),
			const std::vector<int>& _positiveKeys = {}, const std::vector<int>& _negetiveKeys = {},
			float _controlSpeed = 1)
			:aeroPlusOne(_aeroPlusOne),
			aeroMinusOne(_aeroMinusOne),
			positiveKeys(_positiveKeys),
			negetiveKeys(_negetiveKeys),
			controlSpeed(_controlSpeed)
		{

		}
		Vector3 aeroPlusOne;
		Vector3 aeroMinusOne;
		std::vector<int> positiveKeys;
		std::vector<int> negetiveKeys;
		float controlSetting = 0;
		float controlSpeed;
	};
}
