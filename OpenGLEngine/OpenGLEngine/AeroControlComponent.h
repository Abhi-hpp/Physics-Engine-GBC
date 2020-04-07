#pragma once
#include "ECSConfig.h"
<<<<<<< Updated upstream
#include <vector>
=======
>>>>>>> Stashed changes

namespace Reality
{
	struct AeroControlComponent
	{
<<<<<<< Updated upstream
		AeroControlComponent(std::vector<int> _positiveKeys = { GLFW_KEY_UP }, std::vector<int> _negetiveKeys = { GLFW_KEY_DOWN }, float _rate = 1)
			:positiveKeys(_positiveKeys), negetiveKeys(_negetiveKeys), rate(_rate)
		{

		}

		std::vector<int> positiveKeys;
		std::vector<int> negetiveKeys;
		float rate;
=======
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
>>>>>>> Stashed changes
	};
}
