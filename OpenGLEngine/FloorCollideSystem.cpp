#include "FloorCollideSystem.h"
#include "ParticleCollideCheck.h"
#include "TransformComponent.h"
#include "FloorCollideComponent.h"

namespace Reality
{
	FloorCollideSystem::FloorCollideSystem()
	{

	}

	void FloorCollideSystem::Update(float deltaTime)
	{


		for (auto e : getEntities())
		{
			
			if (e.hasComponent<FloorCollideComponent>())
			{

				for (auto s : getEntities())
				{
					if (s.hasComponent<ParticleSphereComponent>())
					{

						auto plane = e.getComponent<FloorCollideComponent>();

						Vector3 pA = plane.A.getComponent<TransformComponent>().position;

						Vector3 pB = plane.B.getComponent<TransformComponent>().position;

						Vector3 pC = plane.C.getComponent<TransformComponent>().position;


						getWorld().data.renderUtil->DrawTriangle(pA, pB, pC, Color(0, 0, 1, 1));


						Vector3 AB = glm::normalize(pB - pA);
						Vector3 AC = glm::normalize(pC - pA);

						Vector3 planeNormal = glm::cross(AB, AC);

						Vector3 unitNormal = glm::normalize(planeNormal);

						auto sphereCenter = s.getComponent<TransformComponent>().position;

						Vector3 randomPoint = sphereCenter - pA;

						float distance = abs(glm::dot(unitNormal, randomPoint));
																											
						if ((distance < s.getComponent<ParticleSphereComponent>().radius)) 
						{
							
							float sumOfAngles = 0;

							Vector3 vA = pA - sphereCenter;
							Vector3 vB = pB - sphereCenter;
							Vector3 vC = pC - sphereCenter;

							float angle1 = acos(glm::dot(vA, vB) / (glm::length(vA) * glm::length(vB)));
							float angle2 = acos(glm::dot(vB, vC) / (glm::length(vB) * glm::length(vC)));
							float angle3 = acos(glm::dot(vA, vC) / (glm::length(vC) * glm::length(vA)));

							sumOfAngles = angle1 + angle2 + angle3;
							sumOfAngles = sumOfAngles / 3.14592654f * 180;

							if (sumOfAngles > 340 && sumOfAngles < 370)
							{

								getWorld().getEventManager().emitEvent<ParticleCollideCheck>(e,	s, 0.8f, unitNormal, s.getComponent<ParticleSphereComponent>().radius - distance);

								getWorld().data.renderUtil->DrawTriangle(pA, pB, pC, Color(1, 0, 0, 1));
							}
						}
							
					}
				}
			}
		

		}
	}
}
