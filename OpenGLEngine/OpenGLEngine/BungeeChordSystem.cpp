#include "BungeeChordSystem.h"
#include "ForceAccumulatorComponent.h"

namespace Reality
{
	BungeeChordSystem::BungeeChordSystem()
	{
		requireComponent<TransformComponent>();
		requireComponent<BungeeChordComponent>();
	}

	void BungeeChordSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& BungeeTransform = e.getComponent<TransformComponent>();
			auto& BungeeSpring = e.getComponent<BungeeChordComponent>();

			if (BungeeSpring.connectedEntity.hasComponent<ForceAccumulatorComponent>()
				&& BungeeSpring.connectedEntity.hasComponent<TransformComponent>())
			{
				auto& forceAcc = BungeeSpring.connectedEntity.getComponent<ForceAccumulatorComponent>();
				auto& transform = BungeeSpring.connectedEntity.getComponent<TransformComponent>();

				Vector3 relativePosition = transform.position - BungeeTransform.position;
				float length = glm::length(relativePosition);
				if (length > 0)
				{
					float deltaL = length - BungeeSpring.BungeeRestLength;

					if (length > BungeeSpring.BungeeRestLength)
					{
						
						Vector3 force = -glm::normalize(relativePosition);
						force *= BungeeSpring.BungeeSpringConstant * deltaL;
						forceAcc.AddForce(force);
					}

					getWorld().data.renderUtil->DrawLine(BungeeTransform.position, transform.position,
						Color::Red);
				}

			}
		}
	}
}
