#include "MutualForceSystem.h"
#include "ParticleComponent.h"

namespace Reality
{
	MutualForceSystem::MutualForceSystem()
	{
		requireComponent<ForceAccumulatorComponent>();
		requireComponent<MutualForceComponent>();
		requireComponent<TransformComponent>();
	}

	void MutualForceSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
			if (e.hasComponent<MutualForceComponent>())
				for (auto h : getEntities())
					if (h.hasComponent<MutualForceComponent>())
						if (e != h)
							CalculateMutualForce(e, h);
	}

	void MutualForceSystem::CalculateMutualForce(ECSEntity& contact, ECSEntity& contact2)
	{
		float massA = contact.hasComponent<ForceAccumulatorComponent>() ?
			contact.getComponent<ForceAccumulatorComponent>().mass : 1;

		float massB = contact2.hasComponent<ForceAccumulatorComponent>() ?
			contact2.getComponent<ForceAccumulatorComponent>().mass : 1;

		Vector3 positionA = contact.hasComponent<TransformComponent>() ?
			contact.getComponent<TransformComponent>().position : Vector3(0, 0, 0);

		Vector3 positionB = contact2.hasComponent<TransformComponent>() ?
			contact2.getComponent<TransformComponent>().position : Vector3(0, 0, 0);

		float distance = sqrt((pow((positionA.x - positionB.x), 2) + pow((positionA.y - positionB.y), 2) + pow((positionA.z - positionB.z), 2)));
		float gPart = 0.1;
		float FinalFormula = (gPart * massA * massB) / pow(distance, 2);

		float lengthA = sqrt(((pow(positionA.x, 2) + pow(positionA.y, 2) + pow(positionA.z, 2)))); //magnitude
		float lengthB = sqrt(((pow(positionB.x, 2) + pow(positionB.y, 2) + pow(positionB.z, 2)))); //magnitude

		Vector3 Direction = positionB - positionA;
		Vector3 test = positionA - positionB;

		Vector3 FinalForceA = (Direction * (FinalFormula * contact.getComponent<MutualForceComponent>().forceScale));

		auto& Accumulator = contact.getComponent<ForceAccumulatorComponent>();

		Accumulator.AddForce(FinalForceA);

		if (DEBUG_LOG_LEVEL > 0)
		{
			//getWorld().data.renderUtil->DrawLine(positionA, positionB, Color::Red);
			//getWorld().data.renderUtil->RenderText("Distance : " + std::to_string(distance), 1650.0f, 960.0f, 0.35f, Color(1, 0, 0, 1));
		}
	}
}
