#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct TriangleComponent
	{
		TriangleComponent(ECSEntity _TriangleA = ECSEntity(), ECSEntity _TriangleB = ECSEntity(), ECSEntity _TriangleC = ECSEntity()) :
			TriangleA(_TriangleA), TriangleB(_TriangleB), TriangleC(_TriangleC), Center(), Normal(),
			A(),
			B(),
			C()
		{



		}

		ECSEntity TriangleA;
		ECSEntity TriangleB;
		ECSEntity TriangleC;
		Vector3 A;
		Vector3 B;
		Vector3 C;
		Vector3 Center;
		Vector3 Normal;
	};
}
