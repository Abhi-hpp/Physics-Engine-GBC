#include "BoxColliderSystem.h"
#include "RigidbodyComponent.h"
#include "ForceAndTorqueAccumulatorComponent.h"
#include "RigidBodySystem.h"

namespace Reality
{
	BoxColliderSystem::BoxColliderSystem(rp3d::CollisionWorld& _rp3dWorld)
		:rp3dWorld(_rp3dWorld)
	{
		requireComponent<BoxColliderComponent>();
	}

	void BoxColliderSystem::Update(float deltaTime)
	{
		std::vector<rp3d::ProxyShape*> rp3dShapesTemp;
		std::vector<int> aliveIds;
		aliveIds.resize(rp3dShapes.size());
		int id = 0;

		for (auto e : getEntities())
		{
			auto &boxCollider = e.getComponent<BoxColliderComponent>();

			if (boxCollider.body.isAlive() && boxCollider.body.hasComponent<RigidbodyComponent>())
			{
				auto &body = boxCollider.body.getComponent<RigidbodyComponent>();

				// Update RP3D Ids
				// Calculate local rp3d transform
				rp3d::Vector3 initPosition(boxCollider.offset.x,
					boxCollider.offset.y,
					boxCollider.offset.z);
				rp3d::Quaternion initOrientation = rp3d::Quaternion(boxCollider.orientation.x, boxCollider.orientation.y, boxCollider.orientation.z, boxCollider.orientation.w);
				rp3d::Transform rp3dtransform(initPosition, initOrientation);

				auto rp3dBody = getWorld().getSystemManager().getSystem<RigidbodySystem>().rp3dBodies[body.rp3dId];
				// If new rigidbody, create an entry
				if (boxCollider.rp3dId < 0)
				{
					rp3d::BoxShape* shape = new rp3d::BoxShape(rp3d::Vector3(boxCollider.size.x, boxCollider.size.y, boxCollider.size.z) * 0.5f);
					// Add the collision shape to the rigid body

					rp3d::ProxyShape * proxyShape = rp3dBody->addCollisionShape(shape, rp3dtransform);
					proxyShape->setUserData(&boxCollider);
					rp3dShapesTemp.push_back(proxyShape);
					if (boxCollider.body.hasComponent<ForceAndTorqueAccumulatorComponent>())
					{
						auto& forceAndTorque = boxCollider.body.getComponent<ForceAndTorqueAccumulatorComponent>();
						forceAndTorque.inertiaTensor[0][0] += (1.0f / 12.0f) * (pow(2 * boxCollider.size.y, 2) + pow(2 * boxCollider.size.z, 2)) / forceAndTorque.inverseMass;
						forceAndTorque.inertiaTensor[1][1] += (1.0f / 12.0f) * (pow(2 * boxCollider.size.z, 2) + pow(2 * boxCollider.size.x, 2)) / forceAndTorque.inverseMass;
						forceAndTorque.inertiaTensor[2][2] += (1.0f / 12.0f) * (pow(2 * boxCollider.size.x, 2) + pow(2 * boxCollider.size.y, 2)) / forceAndTorque.inverseMass;
					}
					
					boxCollider.rp3dId = id;
				}
				else if (boxCollider.body.isAlive())
				{
					rp3d::ProxyShape * shape = rp3dShapes[boxCollider.rp3dId];
					shape->setLocalToBodyTransform(rp3dtransform);
					aliveIds[boxCollider.rp3dId] = 1;
					rp3dShapesTemp.push_back(shape);
					boxCollider.rp3dId = id;
				}
				id++;

				if (boxCollider.body.hasComponent<TransformComponentV2>())
				{
					auto& bodyTransform = boxCollider.body.getComponent<TransformComponentV2>();
					getWorld().data.renderUtil->DrawCube(bodyTransform.GetUnScaledTransformationMatrix() * Vector4(boxCollider.offset, 1.0f), boxCollider.size, bodyTransform.GetOrientation() * boxCollider.orientation);
				}
			}
			else
			{
				// No need to kill it, the death of RB already killed it
				aliveIds[boxCollider.rp3dId] = 1;
				e.kill();
			}
			
		}

		for (int i = 0; i < aliveIds.size(); i++)
		{
			if (aliveIds[i] == 0)
			{
				if (rp3dShapes[i])
				{
					auto shape = rp3dShapes[i]->getCollisionShapePublic();

					if (rp3dShapes[i]->getBody() && rp3dShapes[i]->getBody()->getProxyShapesList())
					{
						rp3dShapes[i]->getBody()->removeCollisionShape(rp3dShapes[i]);
					}
					delete shape;
				}
			}
		}

		rp3dShapes = rp3dShapesTemp;
	}
}
