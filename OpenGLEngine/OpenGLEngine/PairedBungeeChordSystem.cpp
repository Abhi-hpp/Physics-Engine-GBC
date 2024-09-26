#include "PairedBungeeChordSystem.h"
#include "TransformComponent.h"
#include "ForceAccumulatorComponent.h"

namespace Reality
{
	PairedBungeeChordSystem::PairedBungeeChordSystem()
	{
		requireComponent<PairedBungeeChordComponent>();
	}

	void PairedBungeeChordSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& springPaired = e.getComponent<PairedBungeeChordComponent>();

			if (springPaired.connectedEntityA.hasComponent<TransformComponent>()
				&& springPaired.connectedEntityB.hasComponent<TransformComponent>())
			{
				auto& transformA = springPaired.connectedEntityA.getComponent<TransformComponent>();
				auto& transformB = springPaired.connectedEntityB.getComponent<TransformComponent>();

				Vector3 relativePosition = transformA.position - transformB.position;
				float length = glm::length(relativePosition);
				if (length > 0)
				{
					float deltaL = length - springPaired.bungeeRestLength;
					Vector3 force = -glm::normalize(relativePosition);
					force *= springPaired.bungeeSpringConstant * deltaL;

					if (length > springPaired.bungeeRestLength)
					{
						if (springPaired.connectedEntityA.hasComponent<ForceAccumulatorComponent>())
						{
							springPaired.connectedEntityA.getComponent<ForceAccumulatorComponent>().AddForce(force);
						}
						if (springPaired.connectedEntityB.hasComponent<ForceAccumulatorComponent>())
						{
							springPaired.connectedEntityB.getComponent<ForceAccumulatorComponent>().AddForce(-force);
						}
					}

					getWorld().data.renderUtil->DrawLine(transformA.position, transformB.position,
						Color::Blue);
				}

			}
		}
	}
}
