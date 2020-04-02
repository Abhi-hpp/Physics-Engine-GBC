#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct SphereColliderComponent
	{
		SphereColliderComponent(ECSEntity _body = ECSEntity(), float _radius = 1.0f, Vector3 _offset = Vector3(0, 0, 0))
			: body(_body), offset(_offset), radius(_radius), rp3dId(-1)
		{}
		ECSEntity body;
		Vector3 offset;
		float radius;
		int rp3dId = -1;
	};
}
