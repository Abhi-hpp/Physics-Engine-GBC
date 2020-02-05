#include "NBodySystem.h"
#include "ForceAccumulatorComponent.h"
#include "TransformComponent.h"

namespace Reality
{
	NBodySystem::NBodySystem()
	{
		requireComponent<ForceAccumulatorComponent>();
		requireComponent<TransformComponent>();
		requireComponent<NBodyComponent>();
	}

	void NBodySystem::Update(float deltaTime)
	{
		int size = getEntities().size();
		if (getEntities().size() > 1)
		{
			// create Entities
			for (int i = 0; i < getEntities().size() - 1; i++)
			{
				for (int j = i + 1; j < getEntities().size(); j++) 
				{
					Vector3 force = Vector3(0, 0, 0);
					auto& forceAccObjA = getEntities()[i].getComponent<ForceAccumulatorComponent>();
					auto& forceAccObjB = getEntities()[j].getComponent<ForceAccumulatorComponent>();

					auto& nBodyObjA = getEntities()[i].getComponent<NBodyComponent>();
					auto& nBodyObjB = getEntities()[j].getComponent<NBodyComponent>();

					Vector3 objPosA = getEntities()[i].getComponent<TransformComponent>().position;
					Vector3 objPosB = getEntities()[j].getComponent<TransformComponent>().position;

					//setting appropriate mass for the equation
					float objMassA = 1 / getEntities()[i].getComponent<ForceAccumulatorComponent>().inverseMass;
					float objMassB = 1 / getEntities()[j].getComponent<ForceAccumulatorComponent>().inverseMass;

					getWorld().data.renderUtil->DrawSphere(objPosA, objMassA, Color::Red);
					getWorld().data.renderUtil->DrawSphere(objPosB, objMassB, Color::Red);

					Vector3 radius = objPosA - objPosB;
					Vector3 normal = glm::normalize(radius);


					float dis = glm::distance(objPosA, objPosB);

					// adjusts behaviour at close distances
					if (dis < 20)
					{
						dis = 20;
					}

					float rawForce = objMassA * objMassB / (dis * dis);

					if (rawForce > 20)
					{
						float force = rawForce;
					}


					//force in the direction of B - A
					force = normal * (gravityConstant * rawForce);


					forceAccObjA.AddForce(-force * nBodyObjA.G); // force pushing A towards to B
					forceAccObjB.AddForce(force * nBodyObjB.G); // force pushing B towards to A
					
				}
			}
		}
	}
}
