#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct PlaneNormalComponent
	{
		PlaneNormalComponent(ECSEntity a = ECSEntity(),
			ECSEntity b = ECSEntity(),
			ECSEntity c = ECSEntity(),
			ECSEntity d = ECSEntity(),
			Vector3 _Normals = Vector3(0,0,0),
			float _planeDist = 0,
			float _magnitude = 0)
			: entityA(a),
			entityB(b),
			entityC(c),
			entityD(d),
			Normals(_Normals),
			planeDist(_planeDist),
			magnitude(_magnitude)
		{

		}

		ECSEntity entityA;
		ECSEntity entityB;
		ECSEntity entityC;
		ECSEntity entityD;
		Vector3 Normals;
		float planeDist;
		float magnitude;
	};
}
