#pragma once
#include "ECSConfig.h"
#include <React3D/reactphysics3d.h>
#include "ContactEvent.h"
#include <React3D/collision/ContactManifold.h>
#include <React3D/constraint/ContactPoint.h>
#include "RigidbodyComponent.h"
#include "BodyData.h"

namespace Reality
{
	class RP3DCollisionCallback : public rp3d::CollisionCallback
	{
	public:
		RP3DCollisionCallback(ECSWorld& _ecsWorld)
			:ecsWorld(_ecsWorld)
		{

		}

		ECSWorld& ecsWorld;

		virtual void notifyContact(const CollisionCallbackInfo &collisionCallbackInfo) override
		{
			//collisionCallbackInfo.contactManifoldElements
			rp3d::ContactManifoldListElement * listElem = collisionCallbackInfo.contactManifoldElements;
			// For each contact manifold of the body
			for (; listElem != nullptr; listElem = listElem->getNext()) {
				rp3d::ContactManifold * manifold = listElem->getContactManifold();
				// For each contact point of the manifold
				for (; manifold != nullptr; manifold = manifold->getNext()) {
					// Get the contact point
					rp3d::ContactPoint * point = manifold->getContactPoints();

					ECSEntity entityA = ((BodyData*)collisionCallbackInfo.body1->getUserData())->entity;
					ECSEntity entityB = ((BodyData*)collisionCallbackInfo.body2->getUserData())->entity;

					// Get the world - space contact point on body 1
					rp3d::Vector3 pos = point->getLocalPointOnShape1();
					Vector3 posA = Vector3(pos.x, pos.y, pos.z);

					// Get the world - space contact point on body 2
					pos = point->getLocalPointOnShape2();
					Vector3 posB = Vector3(pos.x, pos.y, pos.z);

					// Get the world - space contact normal
					rp3d::Vector3 rp3dNormal = point->getNormal();
					Vector3 normal = Vector3(rp3dNormal.x, rp3dNormal.y, rp3dNormal.z);

					float penetration = point->getPenetrationDepth();
					ecsWorld.getEventManager().emitEvent<ContactEvent>(
						entityA,
						entityB,
						1.0f,
						normal,
						penetration);

				}
			}
		}
	};
}
