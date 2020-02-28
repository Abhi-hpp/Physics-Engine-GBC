#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct BridgeComponent
	{
		BridgeComponent(ECSEntity _E0 = ECSEntity(), ECSEntity _E1 = ECSEntity(), ECSEntity _E2 = ECSEntity())
			: E0(_E0), E1(_E1), E2(_E2)
		{

		}
		ECSEntity E0;
		ECSEntity E1;
		ECSEntity E2;
	};
}
