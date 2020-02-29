#include "NBodySystem.h"
#include "TransformComponent.h"
#include "ForceAccumulatorComponent.h"

namespace Reality
{
	NBodySystem::NBodySystem()
	{
		requireComponent<NBodyComponent>();
		requireComponent<ForceAccumulatorComponent>();
		requireComponent<TransformComponent>();
	}

	void NBodySystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto position1 = e.getComponent<TransformComponent>().position;
			auto& force1 = e.getComponent<ForceAccumulatorComponent>();
			if (force1.inverseMass <= 0) { continue; } //negative mass Skip
			auto mass1 = 1 / force1.inverseMass;
			
			for (auto e2 : getEntities())
			{
				if (e == e2) { continue; }

				auto position2 = e2.getComponent<TransformComponent>().position;
				auto& force2 = e2.getComponent<ForceAccumulatorComponent>();
				if (force2.inverseMass <= 0) { continue; }  //negative mass Skip
				auto mass2 = 1 / force2.inverseMass;

				float length = glm::length(position1 - position2);
				Vector3 force = glm::normalize(position1 - position2);

				float GConst = 300;
				force *= GConst * ((mass1 * mass2) / length);
				force1.AddForce(force);
			}
		}
	}
}
