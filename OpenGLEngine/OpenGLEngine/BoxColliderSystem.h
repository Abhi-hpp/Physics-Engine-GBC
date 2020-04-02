#pragma once
#include "ECSConfig.h"
#include "BoxColliderComponent.h"
#include "TransformComponentV2.h"
#include <React3D/reactphysics3d.h>
namespace Reality
{
	class BoxColliderSystem : public ECSSystem
	{
	public:
		BoxColliderSystem(rp3d::CollisionWorld& _rp3dWorld);
		void Update(float deltaTime);
	private:
		rp3d::CollisionWorld& rp3dWorld;
		std::vector<rp3d::ProxyShape*> rp3dShapes;
	};
}
