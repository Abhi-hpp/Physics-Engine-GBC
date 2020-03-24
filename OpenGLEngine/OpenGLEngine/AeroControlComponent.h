#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct AeroControlComponent
	{
		AeroControlComponent(Mat3 _aeroPlusOne = Mat3(-0.1f), Mat3 _aeroMinusOne = Mat3(0.1f),
			const std::vector<int>& _positiveKeys = {}, const std::vector<int>& _negetiveKeys = {},
			float _controlSpeed = 1)
			:aeroPlusOne(_aeroPlusOne),
			aeroMinusOne(_aeroMinusOne),
			positiveKeys(_positiveKeys),
			negetiveKeys(_negetiveKeys),
			controlSpeed(_controlSpeed)
		{

		}
		Mat3 aeroPlusOne;
		Mat3 aeroMinusOne;
		std::vector<int> positiveKeys;
		std::vector<int> negetiveKeys;
		float controlSetting = 0;
		float controlSpeed;
	};
}
