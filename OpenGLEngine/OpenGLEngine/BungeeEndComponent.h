#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct BungeeEndComponent
	{
		BungeeEndComponent(bool _connectedTo = false) :
			connectedTo(_connectedTo)
		{

		}

		bool connectedTo;
	};
}
