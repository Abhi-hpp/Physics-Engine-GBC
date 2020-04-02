#include "SphereColliderSystem.h"
#include "RigidbodyComponent.h"
#include "ForceAndTorqueAccumulatorComponent.h"
#include "RigidBodySystem.h"

namespace Reality
{
	SphereColliderSystem::SphereColliderSystem(rp3d::CollisionWorld& _rp3dWorld)
		:rp3dWorld(_rp3dWorld)
	{
		requireComponent<SphereColliderComponent>();
	}

	void SphereColliderSystem::Update(float deltaTime)
	{
		std::vector<rp3d::ProxyShape*> rp3dShapesTemp;
		std::vector<int> aliveIds;
		aliveIds.resize(rp3dShapes.size());
		int id = 0;

		for (auto e : getEntities())
		{
			auto &sphereCollider = e.getComponent<SphereColliderComponent>();

			if (sphereCollider.body.isAlive() && sphereCollider.body.hasComponent<RigidbodyComponent>())
			{
				auto &body = sphereCollider.body.getComponent<RigidbodyComponent>();

				// Update RP3D Ids
				// Calculate local rp3d transform
				rp3d::Vector3 initPosition(sphereCollider.offset.x,
					sphereCollider.offset.y,
					sphereCollider.offset.z);
				rp3d::Quaternion initOrientation = rp3d::Quaternion::identity();
				rp3d::Transform rp3dtransform(initPosition, initOrientation);

				auto rp3dBody = getWorld().getSystemManager().getSystem<RigidbodySystem>().rp3dBodies[body.rp3dId];
				// If new rigidbody, create an entry
				if (sphereCollider.rp3dId < 0)
				{
					rp3d::decimal radius = rp3d::decimal(sphereCollider.radius);
					rp3d::SphereShape* shape = new rp3d::SphereShape(radius);
					// Add the collision shape to the rigid body

					rp3d::ProxyShape * proxyShape = rp3dBody->addCollisionShape(shape, rp3dtransform);
					proxyShape->setUserData(&sphereCollider);
					rp3dShapesTemp.push_back(proxyShape);
					if (sphereCollider.body.hasComponent<ForceAndTorqueAccumulatorComponent>())
					{
						auto& forceAndTorque = sphereCollider.body.getComponent<ForceAndTorqueAccumulatorComponent>();
						forceAndTorque.inertiaTensor += Mat3( (2.0f / 5.0f) * pow(sphereCollider.radius, 2)  / forceAndTorque.inverseMass);
					}
					sphereCollider.rp3dId = id;
				}
				else if (sphereCollider.body.isAlive())
				{
					rp3d::ProxyShape * shape = rp3dShapes[sphereCollider.rp3dId];
					shape->setLocalToBodyTransform(rp3dtransform);
					aliveIds[sphereCollider.rp3dId] = 1;
					rp3dShapesTemp.push_back(shape);
					sphereCollider.rp3dId = id;
				}
				id++;

				if (sphereCollider.body.hasComponent<TransformComponentV2>())
				{
					getWorld().data.renderUtil->DrawSphere(sphereCollider.body.getComponent<TransformComponentV2>().GetUnScaledTransformationMatrix() * Vector4(sphereCollider.offset, 1.0f), sphereCollider.radius);
				}
			}
			else
			{
				// No need to kill it, the death of RB already killed it
				aliveIds[sphereCollider.rp3dId] = 1;
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
