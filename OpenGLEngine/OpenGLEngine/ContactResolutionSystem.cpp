#include "ContactResolutionSystem.h"
#include "TransformComponentV2.h"
#include "RigidBodyComponent.h"
#include <string>

namespace Reality
{

	ContactResolutionSystem::ContactResolutionSystem(rp3d::CollisionWorld& _rp3dWorld) : rp3dWorld(_rp3dWorld)
	{
	}

	void ContactResolutionSystem::Update(float deltaTime)
	{
		auto contactEvents = getWorld().getEventManager().getEvents<ContactEvent>();
		for (auto& contact : contactEvents)
		{
			ResolveVelocity(contact);
		}
		getWorld().data.renderUtil->RenderText("Num Contacts = " + to_string(contactEvents.size()), 1920 * 0.5f - 100, 1080 * 0.5f, 0.5f, Color::Red);
	}
	void ContactResolutionSystem::ResolveVelocity(ContactEvent & contact)
	{
		// Get Rigidbodies involved
		auto& rbA = contact.entityA.getComponent<RigidBodyComponent>();
		auto& rbB = contact.entityB.getComponent<RigidBodyComponent>();
		auto& transformA = contact.entityA.getComponent<TransformComponentV2>();
		auto& transformB = contact.entityB.getComponent<TransformComponentV2>();

		// Calculate contact point as avg
		Vector3 contactPoint = (contact.worldPoint1 + contact.worldPoint2) * 0.5f;

		// Calculate contact point basis
		Vector3 contactY;
		Vector3 contactZ;
		Mat3 contactLocalToWorld = Mat3(1.0f);
		CalculateContactBasis(contact.normal, contactLocalToWorld, contactY, contactZ);
		getWorld().data.renderUtil->DrawLine(contactPoint, contactPoint + 5.0f * contact.normal, Color::Red);
		getWorld().data.renderUtil->DrawLine(contactPoint, contactPoint + 5.0f * contactY, Color::Green);
		getWorld().data.renderUtil->DrawLine(contactPoint, contactPoint + 5.0f * contactZ, Color::Blue);

		// Relative Positions
		Vector3 relativePositionA = contactPoint - transformA.GetPosition();
		Vector3 relativePositionB = contactPoint - transformB.GetPosition();

		// World Inertia Tensors
		Mat3 worldInvInertiaTensorA = rbA.worldInverseInertiaTensor(transformA.GetRotationMatrix());
		Mat3 worldInvInertiaTensorB = rbB.worldInverseInertiaTensor(transformB.GetRotationMatrix());

		// Calculate velocity Per Unit Impulse
		// Body A	
		Vector3 torquePerUnitImpulseA = glm::cross(relativePositionA, contact.normal);
		Vector3 rotationPerUnitImpulseA = worldInvInertiaTensorA * torquePerUnitImpulseA;
		Vector3 deltaVelWorldA = glm::cross(rotationPerUnitImpulseA, relativePositionA);

		float deltaVel = glm::dot(deltaVelWorldA, contact.normal);
		deltaVel += rbA.inverseMass;

		//deltaVel = -deltaVel;
		// Body B
		Vector3 torquePerUnitImpulseB = glm::cross(relativePositionB, contact.normal);
		Vector3 rotationPerUnitImpulseB = worldInvInertiaTensorB * torquePerUnitImpulseB;
		Vector3 deltaVelWorldB = glm::cross(rotationPerUnitImpulseB, relativePositionB);

		deltaVel += glm::dot(deltaVelWorldB, contact.normal);
		deltaVel += rbB.inverseMass;

		// Closing Velocity
		Vector3 velocityA = glm::cross(rbA.angularVelocity, relativePositionA);
		velocityA += rbA.velocity;

		Vector3 velocityB = glm::cross(rbB.angularVelocity, relativePositionB);
		velocityB += rbB.velocity;

		Vector3 closingVelocityWorld = velocityA - velocityB;
		Vector3 closingVelocityLocal = glm::transpose(contactLocalToWorld) * closingVelocityWorld;

		if (closingVelocityLocal.x < 0)
		{
			return;
		}
		// Delta Velocity and impulse
		float desiredDeltaVelocityLocal = -closingVelocityLocal.x * (1 + contact.restitution);
		Vector3 impulseContact = Vector3(desiredDeltaVelocityLocal / deltaVel, 0, 0);
		//impulseContact = Vector3(10, 0, 0);
		Vector3 impulseA = contactLocalToWorld * impulseContact;
		Vector3 impulseB = -impulseA;

		// Calculate Velocity Change
		// A
		Vector3 velocityChangeA = impulseA * rbA.inverseMass;
		Vector3 rotationalTorqueA = glm::cross(impulseA, relativePositionA);
		Vector3 angularVelocityChangeA = worldInvInertiaTensorA * rotationalTorqueA;
		rbA.velocity += velocityChangeA;
		rbA.angularVelocity += angularVelocityChangeA;
		// B
		Vector3 velocityChangeB = impulseB * rbB.inverseMass;
		Vector3 rotationalTorqueB = glm::cross(impulseB, relativePositionB);
		Vector3 angularVelocityChangeB = worldInvInertiaTensorB * rotationalTorqueB;
		rbB.velocity += velocityChangeB;
		rbB.angularVelocity += angularVelocityChangeB;

		// Debug Drawing
		getWorld().data.renderUtil->DrawSphere(contact.worldPoint1, 0.4f, Color::Red);
		getWorld().data.renderUtil->DrawSphere(contact.worldPoint2, 0.4f, Color::Blue);
		getWorld().data.renderUtil->DrawLine(contact.worldPoint1, contact.worldPoint2, Color::Beige);
	}
	void ContactResolutionSystem::CalculateContactBasis(Vector3 contactNormal, Mat3 & transformationMat, Vector3 & y, Vector3 & z)
	{
		Vector3 possibleYAxis = Vector3(0, 1, 0);
		if (glm::length(glm::cross(possibleYAxis, contactNormal)) <= 0.01f)
		{
			possibleYAxis = Vector3(0, 0, 1);
		}
		z = glm::normalize(glm::cross(contactNormal, possibleYAxis));
		y = glm::normalize(glm::cross(z, contactNormal));

		transformationMat = Mat3(contactNormal.x, contactNormal.y, contactNormal.z,
									y.x, y.y, y.z,
									z.x, z.y, z.z);
	}
}
