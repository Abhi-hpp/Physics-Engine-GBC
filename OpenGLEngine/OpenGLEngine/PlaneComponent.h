#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct PlaneComponent
	{
		PlaneComponent(ECSEntity _p1 =  ECSEntity(), ECSEntity _p2 = ECSEntity(), ECSEntity _p3 = ECSEntity(), ECSEntity _p4 = ECSEntity()) : p1(_p1), p2(_p2), p3(_p3), p4(_p4)
		{
			
		}

		ECSEntity p1;
		ECSEntity p2;
		ECSEntity p3;
		ECSEntity p4;

		Vector3 normal1;
		Vector3 normal2;

		Vector3 middle1;
		Vector3 middle2;

		float d1;
		float d2;

		vector<ECSEntity> spheres;
	};
}
