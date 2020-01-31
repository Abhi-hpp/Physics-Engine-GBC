#include "NBodySystem.h"
#include "ParticleComponent.h"
#include "ForceAccumulatorComponent.h"
#include "TransformComponent.h"

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
		int count = getEntities().size();

			for(int i = 0; i < count; i++)
			{
				for(int j = i + 1 ; j < count; j++)
				{
					Vector3 spaceBetween = Vector3(getEntities()[i].getComponent<TransformComponent>().position - getEntities()[j].getComponent<TransformComponent>().position);

					float magnitude = (getEntities()[i].getComponent<NBodyComponent>().mass * getEntities()[j].getComponent<NBodyComponent>().mass * 4) /
						pow(glm::length(spaceBetween), 2);
					// POP POP!

					Vector3 force = glm::normalize(spaceBetween) * abs(magnitude);

					getEntities()[i].getComponent<ForceAccumulatorComponent>().AddForce(-force);
					getEntities()[j].getComponent<ForceAccumulatorComponent>().AddForce(force);
					/*

					*/
				}
			}

			
		for (auto e : getEntities())
		{
			
				getWorld().data.renderUtil->DrawSphere(e.getComponent<TransformComponent>().position, e.getComponent<NBodyComponent>().mass, Color(e.getComponent<NBodyComponent>().mass/500.0, 0.0f, 1.0f));
				getWorld().data.renderUtil->DrawSphere(e.getComponent<TransformComponent>().position, e.getComponent<NBodyComponent>().mass, Color(e.getComponent<NBodyComponent>().mass/500.0, 0.0f, 1.0f));
					
		}
		
	}
}
