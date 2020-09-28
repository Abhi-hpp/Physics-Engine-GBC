#pragma once
#include "ECSConfig.h"
#include <React3D/reactphysics3d.h>

namespace Reality
{
	struct SphereColliderComponent
	{
		SphereColliderComponent(ECSEntity _rigidbodyEntity = ECSEntity(), float _radius = 1.0f)
		{

		}
		ECSEntity rigidbodyEntity;
		float radius;
		rp3d::ProxyShape* proxyShape;
		bool initialized = false;
	};
}
