#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct BridgeRodComponent
	{
		BridgeRodComponent(ECSEntity a = ECSEntity(), ECSEntity b = ECSEntity(), float _rodMaxLength = 10)
			: entityA(a), entityB(b), rodMaxLength(_rodMaxLength)
		{

		}
		ECSEntity entityA;
		ECSEntity entityB;
		float rodMaxLength;
	};
}
