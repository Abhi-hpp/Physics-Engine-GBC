#include "NBodySystem.h"

namespace Reality
{
	NBodySystem::NBodySystem()
	{
		requireComponent<TransformComponent>();
		requireComponent<NBodyComponent>();
		requireComponent<ForceAccumulatorComponent>();
	}

	void NBodySystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& transfA = e.getComponent<TransformComponent>();
			auto& forceAccA = e.getComponent<ForceAccumulatorComponent>();
			auto& nBodyA = e.getComponent<NBodyComponent>();

			for (auto f : getEntities())
			{
				auto& transfB = f.getComponent<TransformComponent>();
				auto& forceAccB = f.getComponent<ForceAccumulatorComponent>();
				auto& nBodyB = f.getComponent<NBodyComponent>();

				if (e != f)
				{
					Vector3 relativePosition = transfA.position - transfB.position;
					float length = glm::length(relativePosition);

					if (length <= 0)
					{
						return;
					}
					else
					{
						float forceConstant = (nBodyB.gVariable * nBodyA.mass * nBodyB.mass) / pow(length, 2);
						Vector3 forceDir = glm::normalize(relativePosition);

						if (forceConstant > 100)
						{
							forceConstant = 100;
						}

						forceAccA.AddForce(forceConstant * -forceDir);
						forceAccB.AddForce(forceConstant * forceDir);
					}
				}
			}
		}
	}
}
