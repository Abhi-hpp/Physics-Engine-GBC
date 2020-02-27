#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct PlaneComponent
	{
		PlaneComponent(ECSEntity _e1 = ECSEntity(), ECSEntity _e2 = ECSEntity(), ECSEntity _e3 = ECSEntity(), ECSEntity _e4 = ECSEntity()) :
			e1(_e1),
			e2(_e2),
			e3(_e3),
			e4(_e4),
			bIsColliding1(false),
			bIsColliding2(false),
			normal1(),
			normal2(),
			Center1(),
			Center2()
		{

		}

		bool bIsColliding1;
		bool bIsColliding2;
		Vector3 normal1;
		Vector3 normal2;
		Vector3 Center1;
		Vector3 Center2;
		ECSEntity e1;
		ECSEntity e2;
		ECSEntity e3;
		ECSEntity e4;
	};
}
