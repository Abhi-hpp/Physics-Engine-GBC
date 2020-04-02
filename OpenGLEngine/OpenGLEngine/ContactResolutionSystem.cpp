#include "ContactResolutionSystem.h"
#include "TransformComponentV2.h"
#include "RigidbodyComponent.h"
#include "ForceAndTorqueAccumulatorComponent.h"
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
			ResolvePenetration(contact);
			ResolveVelocity(contact);
		}
		getWorld().data.renderUtil->RenderText("Num Contacts = " + to_string(contactEvents.size()), 1920 * 0.5f - 100, 1080 * 0.5f, 0.5f, Color::Red);
	}
	void ContactResolutionSystem::ResolvePenetration(ContactEvent & contact)
	{
		// Get Rigidbodies involved
		auto& rbA = contact.entityA.getComponent<RigidbodyComponent>();
		auto& rbB = contact.entityB.getComponent<RigidbodyComponent>();
		auto& ftA = contact.entityA.getComponent<ForceAndTorqueAccumulatorComponent>();
		auto& ftB = contact.entityB.getComponent<ForceAndTorqueAccumulatorComponent>();
		auto& transformA = contact.entityA.getComponent<TransformComponentV2>();
		auto& transformB = contact.entityB.getComponent<TransformComponentV2>();

		// Calculate contact point as avg
		Vector3 contactPoint = (contact.worldPoint1 + contact.worldPoint2) * 0.5f;

		// Relative Positions
		Vector3 relativePositionA = contact.worldPoint1 - transformA.GetPosition();
		Vector3 relativePositionB = contact.worldPoint2 - transformB.GetPosition();
		contact.normal *= -1;
		// World Inertia Tensors
		Mat3 worldInvInertiaTensorA = ftA.GetWorldInverseInertiaTensor(transformA.GetRotationMatrix());
		Mat3 worldInvInertiaTensorB = ftB.GetWorldInverseInertiaTensor(transformB.GetRotationMatrix());

		float totalInertia = 0;

		Vector3 angularInertiaWorldA = glm::cross(relativePositionA, contact.normal);
		angularInertiaWorldA = worldInvInertiaTensorA * angularInertiaWorldA;
		angularInertiaWorldA = glm::cross(angularInertiaWorldA, relativePositionA);

		float angularInertiaA = glm::dot(angularInertiaWorldA, contact.normal);
		float linearInertiaA = ftA.inverseMass;
		totalInertia += angularInertiaA + linearInertiaA;

		Vector3 angularInertiaWorldB = glm::cross(relativePositionB, contact.normal);
		angularInertiaWorldB = worldInvInertiaTensorB * angularInertiaWorldB;
		angularInertiaWorldB = glm::cross(angularInertiaWorldB, relativePositionB);

		float angularInertiaB = glm::dot(angularInertiaWorldB, contact.normal);
		float linearInertiaB = ftB.inverseMass;
		totalInertia += angularInertiaB + linearInertiaB;

		// Total Moves
		float inverseInertia = 1 / totalInertia; 
		float linearMoveA = contact.penetrationDepth * linearInertiaA * inverseInertia; 
		float linearMoveB = -contact.penetrationDepth * linearInertiaB * inverseInertia;
		float angularMoveA = contact.penetrationDepth * angularInertiaA * inverseInertia;
		float angularMoveB = -contact.penetrationDepth * angularInertiaB * inverseInertia;

		float limitA = angularLimitConstant * glm::length(relativePositionA);
		if (abs(angularMoveA) > limitA)
		{
			float totalMoveA = linearMoveA + angularMoveA;
			// Set the new angular move, with the same sign as before. 
			if (angularMoveA >= 0) 
			{ 
				angularMoveA = limitA; 
			} else 
			{ 
				angularMoveA = -limitA; 
			}
			// Make the linear move take the extra slack. 
			linearMoveA = totalMoveA - angularMoveA;
		}

		float limitB = angularLimitConstant * glm::length(relativePositionB);
		if (abs(angularMoveB) > limitB)
		{
			float totalMoveB = linearMoveB + angularMoveB;
			// Set the new angular move, with the same sign as before. 
			if (angularMoveB >= 0)
			{
				angularMoveB = limitB;
			}
			else
			{
				angularMoveB = -limitB;
			}
			// Make the linear move take the extra slack. 
			linearMoveB = totalMoveB - angularMoveB;
		}

		// Update Linear Moves
		transformA.SetPosition(transformA.GetPosition() + contact.normal * linearMoveA);
		transformB.SetPosition(transformB.GetPosition() + contact.normal * linearMoveB);

		// Update Rotational Moves
		// A
		Vector3 impulsiveTorqueA = glm::cross(relativePositionA,  contact.normal); 
		Vector3 impulsePerMoveA = worldInvInertiaTensorA * impulsiveTorqueA;

		Vector3 rotationPerMoveA = impulsePerMoveA * (1 / angularInertiaA);
		Vector3 rotationA = rotationPerMoveA * angularMoveA;

		glm::quat rotationQuatA = glm::quat(0, rotationA.x, rotationA.y, rotationA.z);
		glm::quat finalOrientationA = transformA.GetOrientation() + 0.5f * rotationQuatA * transformA.GetOrientation();
		if (glm::length(finalOrientationA) > 0)
		{
			transformA.SetOrientation(glm::normalize(finalOrientationA));
		}

		// B
		Vector3 impulsiveTorqueB = glm::cross(relativePositionB, contact.normal);
		Vector3 impulsePerMoveB = worldInvInertiaTensorB * impulsiveTorqueB;

		Vector3 rotationPerMoveB = impulsePerMoveB * (1 / angularInertiaB);
		Vector3 rotationB = rotationPerMoveB * angularMoveB;

		glm::quat rotationQuatB = glm::quat(0, rotationB.x, rotationB.y, rotationB.z);
		glm::quat finalOrientationB = transformB.GetOrientation() + 0.5f * rotationQuatB * transformB.GetOrientation();
		if (glm::length(finalOrientationB) > 0)
		{
			transformB.SetOrientation(glm::normalize(finalOrientationB));
		}
		contact.normal *= -1;

	}
	void ContactResolutionSystem::ResolveVelocity(ContactEvent & contact)
	{
		// Get Rigidbodies involved
		auto& rbA = contact.entityA.getComponent<RigidbodyComponent>();
		auto& rbB = contact.entityB.getComponent<RigidbodyComponent>();
		auto& ftA = contact.entityA.getComponent<ForceAndTorqueAccumulatorComponent>();
		auto& ftB = contact.entityB.getComponent<ForceAndTorqueAccumulatorComponent>();
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
		Vector3 relativePositionA = contact.worldPoint1 - transformA.GetPosition();
		Vector3 relativePositionB = contact.worldPoint2 - transformB.GetPosition();

		// World Inertia Tensors
		Mat3 worldInvInertiaTensorA = ftA.GetWorldInverseInertiaTensor(transformA.GetRotationMatrix());
		Mat3 worldInvInertiaTensorB = ftB.GetWorldInverseInertiaTensor(transformB.GetRotationMatrix());

		// Calculate velocity Per Unit Impulse
		// Body A	
		Vector3 torquePerUnitImpulseA = glm::cross(relativePositionA, contact.normal);
		Vector3 rotationPerUnitImpulseA = worldInvInertiaTensorA * torquePerUnitImpulseA;
		Vector3 deltaVelWorldA = glm::cross(rotationPerUnitImpulseA, relativePositionA);

		float deltaVel = glm::dot(deltaVelWorldA, contact.normal);
		deltaVel += ftA.inverseMass;

		// Body B
		Vector3 torquePerUnitImpulseB = glm::cross(relativePositionB, contact.normal);
		Vector3 rotationPerUnitImpulseB = worldInvInertiaTensorB * torquePerUnitImpulseB;
		Vector3 deltaVelWorldB = glm::cross(rotationPerUnitImpulseB, relativePositionB);

		deltaVel += glm::dot(deltaVelWorldB, contact.normal);
		deltaVel += ftB.inverseMass;

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
		float desiredDeltaVelocityLocal = -closingVelocityLocal.x * (1 + 0.4f);
		Vector3 impulseContact = Vector3(desiredDeltaVelocityLocal / deltaVel, 0, 0);
		Vector3 impulseA = contactLocalToWorld * impulseContact;
		Vector3 impulseB = -impulseA;

		// Calculate Velocity Change
		// A
		Vector3 velocityChangeA = impulseA * ftA.inverseMass;
		Vector3 rotationalTorqueA = glm::cross(relativePositionA, impulseA);
		Vector3 angularVelocityChangeA = worldInvInertiaTensorA * rotationalTorqueA;
		rbA.velocity += velocityChangeA;
		rbA.angularVelocity += angularVelocityChangeA;
		// B
		Vector3 velocityChangeB = impulseB * ftB.inverseMass;
		Vector3 rotationalTorqueB = glm::cross(relativePositionB, impulseB);
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
		Vector3 possibleYAxis = Vector3(0, 1.0f, 0);
		if (glm::length(glm::cross(possibleYAxis, contactNormal)) <= 0.01f)
		{
			possibleYAxis = Vector3(0, 0, 1.0f);
		}
		z = glm::normalize(glm::cross(contactNormal, possibleYAxis));
		y = glm::normalize(glm::cross(z, contactNormal));

		transformationMat = Mat3(contactNormal.x, contactNormal.y, contactNormal.z,
									y.x, y.y, y.z,
									z.x, z.y, z.z);
	}
}
