#include "BridgeSystem.h"
#include "TransformComponent.h"
#include "ParticleContactEvent.h"

namespace Reality
{
	BridgeSystem::BridgeSystem()
	{
		requireComponent<BridgeComponent>();
	}

	void BridgeSystem::Update(float deltaTime)
	{
		if (Sphere != 99)
		{
			for (auto e : getEntities())
			{
				auto& bTriangle = e.getComponent<BridgeComponent>();

				Vector3 pos0 = bTriangle.E0.getComponent<TransformComponent>().position;
				Vector3 pos1 = bTriangle.E1.getComponent<TransformComponent>().position;
				Vector3 pos2 = bTriangle.E2.getComponent<TransformComponent>().position;
				Vector3 center = (pos0 + pos1 + pos2) / 3.0f;

				Vector3 vec1 = pos1 - pos0;
				Vector3 vec2 = pos2 - pos0;
				Vector3 Normal = glm::normalize(glm::cross(vec1, vec2));
				float planeDirection = -(Normal.x * center.x + Normal.y * center.y + Normal.z * center.z);

				Normal = glm::normalize(Normal);
				getWorld().data.renderUtil->DrawLine(center, center + (Normal), Color(0, 0, 1, 1));

				Vector4 plane = Vector4(Normal, planeDirection);
				Vector4 pSphere = Vector4(Sphere.getComponent<TransformComponent>().position, 1);
				float distanceSP = glm::dot(plane, pSphere);

				Vector3 direction = Vector3(pSphere) - center;
				direction = glm::normalize(direction);



				// Math and Calculations Part

				Vector3 u = pos1 - pos0;

				Vector3 v = pos2 - pos0;

				Vector3 n = glm::cross(u, v);

				Vector3 w = Sphere.getComponent<TransformComponent>().position - pos0;

				float gamma = glm::dot(glm::cross(u, w), n) / glm::dot(n, n);

				float beta = glm::dot(glm::cross(w, v), n) / glm::dot(n, n);
				float alpha = 1 - gamma - beta;

				if ((0 <= alpha) && (alpha <= 1) &&
					(0 <= beta) && (beta <= 1) &&
					(0 <= gamma) && (gamma <= 1)) 
				{
					if (abs(distanceSP) < 1)
					{
						float penetration = 1 - distanceSP;

						getWorld().getEventManager().emitEvent<ParticleContactEvent>(
							bTriangle.E0, Sphere, 0.8f, -Normal, penetration);
						
						
						getWorld().getEventManager().emitEvent<ParticleContactEvent>(
							bTriangle.E1, Sphere, 0.8f, -Normal, penetration);

						getWorld().getEventManager().emitEvent<ParticleContactEvent>(
							bTriangle.E2, Sphere, 0.8f, -Normal, penetration);
					}

					getWorld().data.renderUtil->DrawLine(center, center + (Normal * distanceSP), Color(0, 1, 0, 1));
				}
				else
				{
					getWorld().data.renderUtil->DrawLine(center, center + (Normal * distanceSP), Color(1, 0, 0, 1));
				}
			}
		}
	}
}
