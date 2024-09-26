#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct BuoyancyControlEvent
	{
		BuoyancyControlEvent(string _command = "") :
			command(_command)
		{

		}

		string command;
	};
}
