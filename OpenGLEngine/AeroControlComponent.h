#pragma once
#include "ECSConfig.h"
#include <vector>

namespace Reality
{
	struct AeroControlComponent
	{
		AeroControlComponent(std::vector<int> _positiveKeys = { GLFW_KEY_UP }, std::vector<int> _negetiveKeys = { GLFW_KEY_DOWN }, float _rate = 1)
			:positiveKeys(_positiveKeys), negetiveKeys(_negetiveKeys), rate(_rate)
		{

		}

		std::vector<int> positiveKeys;
		std::vector<int> negetiveKeys;
		float rate;
	};
}
