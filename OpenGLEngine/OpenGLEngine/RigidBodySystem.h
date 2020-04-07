#pragma once
#include "ECSConfig.h"
<<<<<<< Updated upstream
#include "RigidBodyComponent.h"
#include "TransformComponentV2.h"
#include <React3D/reactphysics3d.h>

namespace Reality
{
	class RigidBodySystem : public ECSSystem
	{
	public:
		RigidBodySystem(rp3d::CollisionWorld& _rp3dWorld);
		void Update(float deltaTime);
		rp3d::CollisionWorld& rp3dWorld;
		std::vector<rp3d::CollisionBody*> rp3dBodies;
=======
#include "TransformComponentV2.h"
#include "RigidbodyComponent.h"

namespace Reality
{
	class RigidbodySystem : public ECSSystem
	{
	public:
		RigidbodySystem();
		void Update(float deltaTime);
>>>>>>> Stashed changes
	};
}
