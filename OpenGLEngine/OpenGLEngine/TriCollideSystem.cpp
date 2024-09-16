#include "TriCollideSystem.h"
#include "ParticleContactEvent.h"
#include "TransformComponent.h"
#include "TriCollideComponent.h"

namespace Reality
{
	TriCollideSystem::TriCollideSystem()
	{
		//requireComponent<TransformComponent>();
	}

	void TriCollideSystem::Update(float deltaTime)
	{


		for (auto e : getEntities())
		{
			
			if (e.hasComponent<TriCollideComponent>())
			{
				//cout << "It's got triangle collider!" << endl;

				for (auto s : getEntities())
				{
					if (s.hasComponent<ParticleSphereComponent>())
					{
						//cout << "It's got sphere!" << endl;



						auto plane = e.getComponent<TriCollideComponent>();

						Vector3 pA = plane.A.getComponent<TransformComponent>().position;

						Vector3 pB = plane.B.getComponent<TransformComponent>().position;

						Vector3 pC = plane.C.getComponent<TransformComponent>().position;


						getWorld().data.renderUtil->DrawTriangle(pA, pB, pC, Color(1, 1, 1, 1));


						Vector3 AB = glm::normalize(pB - pA);
						Vector3 AC = glm::normalize(pC - pA);

						Vector3 PlaneNorm = glm::cross(AB, AC);

						//float d = -1.0f * (PlaneNorm.x + PlaneNorm.y + PlaneNorm.z);

						//Vector4 PlaneVals = Vector4(PlaneNorm.x, PlaneNorm.y, PlaneNorm.z, d);


						Vector3 UnitNorm = glm::normalize(PlaneNorm);

						auto sphereCenter = s.getComponent<TransformComponent>().position;

						Vector3 someThing = sphereCenter - pA;

						//float D = - (PlaneNorm.x * sphereCenter.x) - (PlaneNorm.y * sphereCenter.y) - (PlaneNorm.z * sphereCenter.z);

						//float distance = (abs(glm::dot(UnitNorm, someThing)) + D) / glm::length(PlaneNorm);

						float distance = abs(glm::dot(UnitNorm, someThing));

						//cout << distance << endl;
																												// Yes.
						if ((distance < s.getComponent<ParticleSphereComponent>().radius)) // 
						{
							
							float angleSum = 0;

							Vector3 vA = pA - sphereCenter;
							Vector3 vB = pB - sphereCenter;
							Vector3 vC = pC - sphereCenter;

							float angle1 = acos(glm::dot(vA, vB) / (glm::length(vA) * glm::length(vB)));
							float angle2 = acos(glm::dot(vB, vC) / (glm::length(vB) * glm::length(vC)));
							float angle3 = acos(glm::dot(vA, vC) / (glm::length(vC) * glm::length(vA)));

							angleSum = angle1 + angle2 + angle3;
							angleSum = angleSum / 3.14592654f * 180;

							if (angleSum > 340 && angleSum < 370)
							{



								cout << "IT'S WORKING! IT'S WOOOOOOOOOOOOOKIIIIIIIIIIN!" << endl;

								getWorld().getEventManager().emitEvent<ParticleContactEvent>(
									e,
									s,
									0.8f,
									UnitNorm,
									s.getComponent<ParticleSphereComponent>().radius - distance);
								

								getWorld().data.renderUtil->DrawTriangle(pA, pB, pC, Color(1, 0, 0, 1));

								getWorld().data.renderUtil->DrawTriangle(pA, pB, pC, Color(1, 0, 0, 1));
							}
						}
							
					}
				}
			}
		

		}
	}
}
