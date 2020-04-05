#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct RopeBridgeComponent
	{
		RopeBridgeComponent(ECSEntity e1 = ECSEntity(), ECSEntity e2 = ECSEntity(), ECSEntity e3 = ECSEntity(),
							ECSEntity e4 = ECSEntity(),ECSEntity e5 = ECSEntity(), ECSEntity e6 = ECSEntity(),
							ECSEntity e7 = ECSEntity(), ECSEntity e8 = ECSEntity(), ECSEntity e9 = ECSEntity(),
							ECSEntity e10 = ECSEntity(), ECSEntity e11 = ECSEntity(), ECSEntity e12 = ECSEntity(),
							ECSEntity e13 = ECSEntity(), ECSEntity e14 = ECSEntity(), ECSEntity e15 = ECSEntity(),
							ECSEntity e16 = ECSEntity(), ECSEntity e17 = ECSEntity(), ECSEntity e18 = ECSEntity(),
							ECSEntity e19 = ECSEntity(), ECSEntity e20 = ECSEntity(), ECSEntity ball = ECSEntity())
			: entity1(e1), entity2(e2), entity3(e3), entity4(e4), entity5(e5), entity6(e6),
			  entity7(e7), entity8(e8), entity9(e9), entity10(e10), entity11(e11), entity12(e12),
			  entity13(e13), entity14(e14), entity15(e15), entity16(e16), entity17(e17), entity18(e18),
			  entity19(e19), entity20(e20), ball(ball) {}

		ECSEntity entity1;
		ECSEntity entity2;
		ECSEntity entity3;
		ECSEntity entity4;
		ECSEntity entity5;
		ECSEntity entity6;
		ECSEntity entity7;
		ECSEntity entity8;
		ECSEntity entity9;
		ECSEntity entity10;
		ECSEntity entity11;
		ECSEntity entity12;
		ECSEntity entity13;
		ECSEntity entity14;
		ECSEntity entity15;
		ECSEntity entity16;
		ECSEntity entity17;
		ECSEntity entity18;
		ECSEntity entity19;
		ECSEntity entity20;

		ECSEntity ball;
	};
}
