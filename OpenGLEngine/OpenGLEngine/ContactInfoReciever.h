#pragma once
#include "ECSConfig.h"
#include "ContactEvent.h"
#include "RigidBodyData.h"
#include <React3D/reactphysics3d.h>
#include <React3D/collision/ContactManifold.h>
#include <React3D/constraint/ContactPoint.h>
namespace Reality
{
	class ContactInfoReciever : public rp3d::CollisionCallback
	{
	public:
		ContactInfoReciever(ECSWorld& _world) : world(_world) {}
		ECSWorld& world;
		void notifyContact(const CollisionCallbackInfo& collisionCallbackInfo)
		{
			rp3d::ContactManifoldListElement * listElem = collisionCallbackInfo.contactManifoldElements;
			// For each contact manifold
			for (; listElem != nullptr; listElem = listElem->getNext()) {
				rp3d::ContactManifold * manifold = listElem->getContactManifold();
				// Get the contact point
				rp3d::ContactPoint * point = manifold->getContactPoints();
				// For each contact point of the manifold
				for (int i = 0; i < manifold->getNbContactPoints(); i++) {
					// Get the world - space contact point on body 1
					rp3d::Vector3 pos1 = point->getLocalPointOnShape1();
					// Get the world - space contact point on body 1
					rp3d::Vector3 pos2 = point->getLocalPointOnShape2();
					// Get the world - space contact normal
					rp3d::Vector3 normal = point->getNormal();
					normal.normalize();
					// Get the penetration
					rp3d::decimal penetration = point->getPenetrationDepth();
					// Get Body 1
					rp3d::CollisionBody* body1 = manifold->getBody1();
					assert(body1);
					RigidBodyData* bodyA = (RigidBodyData*)(manifold->getBody1()->getUserData());
					// Get Body 2
					rp3d::CollisionBody* body2 = manifold->getBody2();
					assert(body2);
					RigidBodyData* bodyB = (RigidBodyData*)(manifold->getBody2()->getUserData());
					// Get Collider 1
					rp3d::ProxyShape* shape1 = manifold->getShape1();
					assert(shape1);
					// Get Collider 2
					rp3d::ProxyShape* shape2 = manifold->getShape2();
					assert(shape2);
					// Get World Point 1
					rp3d::Vector3 worldPos1 = shape1->getLocalToWorldTransform() * pos1;
					// Get World Point 2
					rp3d::Vector3 worldPos2 = shape2->getLocalToWorldTransform() * pos2;
					// Create a contact event
					world.getEventManager().emitEvent<ContactEvent>(bodyA->entity, bodyB->entity,
						Vector3(normal.x, normal.y, normal.z),
						penetration,
						Vector3(pos1.x, pos1.y, pos1.z),
						Vector3(pos2.x, pos2.y, pos2.z),
						Vector3(worldPos1.x, worldPos1.y, worldPos1.z),
						Vector3(worldPos2.x, worldPos2.y, worldPos2.z));
					// Go to the next point in the list
					point = point->getNext();
				}
			}
		}
	};
}
