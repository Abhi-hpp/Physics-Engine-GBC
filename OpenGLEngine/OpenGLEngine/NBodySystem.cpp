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
			for (int i = 0; i < getEntities().size() - 1; i++)
			{
				for (int j = i + 1; j < getEntities().size(); j++) // go though every pair only once
				{
					Vector3 force = Vector3(0, 0, 0);
					auto& forceAccA = getEntities()[i].getComponent<ForceAccumulatorComponent>();
					auto& forceAccB = getEntities()[j].getComponent<ForceAccumulatorComponent>();

					auto& nBodyA = getEntities()[i].getComponent<NBodyComponent>();
					auto& nBodyB = getEntities()[j].getComponent<NBodyComponent>();

					Vector3 posA = getEntities()[i].getComponent<TransformComponent>().position;
					Vector3 posB = getEntities()[j].getComponent<TransformComponent>().position;

					// convert inverse mass to regular for gravity equation
					float massA = 1 / getEntities()[i].getComponent<ForceAccumulatorComponent>().inverseMass;
					float massB = 1 / getEntities()[j].getComponent<ForceAccumulatorComponent>().inverseMass;


					getWorld().data.renderUtil->DrawSphere(posA, massA, Color::Green);
					getWorld().data.renderUtil->DrawSphere(posB, massB, Color::Green);

					//the radius is the vector between the two points positions
					Vector3 radius = posA - posB;
					Vector3 normal = glm::normalize(radius);
					float distance = glm::distance(posA, posB);

					//if the nbodies are closse the small distance cuases them to shoot off
					// adjusts behaviour at close distances
					if (distance < 10)
					{
						distance = 10;
					}
					float rawForce = massA * massB / (distance * distance);
					if (rawForce > 10)
					{
						float force = rawForce;
					}
					//this force is in the direction of B to A
					force = normal * (gravConstant * rawForce);

					//used to visualize the forces for the interaction between nBodies
					/*getWorld().data.renderUtil->DrawLine(posA, posA-force, Color::Red);
					getWorld().data.renderUtil->DrawLine(posB, posB + force, Color::Green);*/

					forceAccA.AddForce(-force * nBodyA.gravityScale); // need the force to push A towards B
					forceAccB.AddForce(force * nBodyB.gravityScale); // need the force to push B towards A
					

				}
			}
		}
	}
}
