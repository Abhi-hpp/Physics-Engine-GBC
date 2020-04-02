#include "RigidbodySystem.h"
#include "RigidbodyData.h"

namespace Reality
{
	RigidbodySystem::RigidbodySystem(rp3d::CollisionWorld& _rp3dWorld)
		:rp3dWorld(_rp3dWorld)
	{
		requireComponent<TransformComponentV2>();
		requireComponent<RigidbodyComponent>();
	}

	void RigidbodySystem::Update(float deltaTime)
	{
		std::vector<rp3d::CollisionBody*> rp3dBodiesTemp;
		std::vector<int> aliveIds;
		aliveIds.resize(rp3dBodies.size());
		int id = 0;

		for (auto e : getEntities())
		{
			auto &rigidbody = e.getComponent<RigidbodyComponent>();
			auto &transform = e.getComponent<TransformComponentV2>();

			// Update RP3D Ids
			// Calculate rp3d transform
			rp3d::Vector3 initPosition(transform.GetPosition().x,
				transform.GetPosition().y,
				transform.GetPosition().z);
			Quaternion quat = transform.GetOrientation();
			rp3d::Quaternion initOrientation = rp3d::Quaternion(
				quat.x, quat.y, quat.z, quat.w);
			rp3d::Transform rp3dtransform(initPosition, initOrientation);
			// If new rigidbody, create an entry
			if (rigidbody.rp3dId < 0)
			{
				rp3d::CollisionBody * body = rp3dWorld.createCollisionBody(rp3dtransform);
				RigidBodyData* data = new RigidBodyData(e);
				body->setUserData(data);
				rp3dBodiesTemp.push_back(body);
				rigidbody.rp3dId = id;
			}
			else
			{
				rp3d::CollisionBody * body = rp3dBodies[rigidbody.rp3dId];
				body->setTransform(rp3dtransform);
				aliveIds[rigidbody.rp3dId] = 1;
				rp3dBodiesTemp.push_back(body);
				rigidbody.rp3dId = id;
			}
			id++;

			// Update velocity from accelarartion
			rigidbody.velocity += (rigidbody.acceleration) * deltaTime;
			rigidbody.angularVelocity += rigidbody.angularAcceleration * deltaTime;

			transform.SetPosition(transform.GetPosition() + rigidbody.velocity * deltaTime);
			glm::quat angularVelocityQuat = glm::quat(0, rigidbody.angularVelocity.x, rigidbody.angularVelocity.y, rigidbody.angularVelocity.z);
			getWorld().data.renderUtil->DrawLine(transform.GetPosition(), transform.GetPosition() + rigidbody.angularVelocity, Color::Blue);
			transform.SetOrientation(glm::normalize(transform.GetOrientation() + 0.5f * angularVelocityQuat * transform.GetOrientation() * deltaTime));
		}

		for (int i = 0; i < aliveIds.size(); i++)
		{
			if (aliveIds[i] == 0)
			{
				rp3dWorld.destroyCollisionBody(rp3dBodies[i]);
			}
		}

		rp3dBodies = rp3dBodiesTemp;
	}
}
