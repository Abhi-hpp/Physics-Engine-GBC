#include "TriangleSystem.h"
#include "TransformComponent.h"
#include "ParticleSphereComponent.h"
#include "ParticleContactEvent.h"
namespace Reality
{
	TriangleSystem::TriangleSystem()
	{
		requireComponent<TriangleComponent>();
	}

	void TriangleSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			if (!e.hasTag("ball"))
			{
				auto& Trig = e.getComponent<TriangleComponent>();

				Vector3 A = Trig.TriangleA.getComponent<TransformComponent>().position;
				Vector3 B = Trig.TriangleB.getComponent<TransformComponent>().position;
				Vector3 C = Trig.TriangleC.getComponent<TransformComponent>().position;

				Trig.A = A;
				Trig.B = B;
				Trig.C = C;

				Trig.Center = Vector3((A.x + B.x + C.x) / 3, (A.y + B.y + C.y) / 3, (A.z + B.z + C.z) / 3);

				Trig.Normal = -glm::normalize(glm::cross(Vector3(A - B), Vector3(A - C)));

				getWorld().data.renderUtil->DrawLine(Trig.Center, Trig.Center + Trig.Normal, Color::Red);

				Vector3 AB = B - A;
				Vector3 AC = C - A;
				Vector3 n = glm::cross(AB, AC);
				
				//getWorld().data.renderUtil->DrawTriangle(A, B, C, Color::Green);

				for (auto e2 : getEntities())
				{
					if (e2.hasTag("ball"))
					{
						
						Vector3 position = e2.getComponent<TransformComponent>().position;
						float radius = e2.getComponent<ParticleSphereComponent>().radius;
						float dist = glm::abs(glm::dot((position - Trig.Center), Trig.Normal));
						if (dist < radius)
						{
							Vector3 AToPlayerDist = position - A;

							float DX = glm::dot(glm::cross(AB, AToPlayerDist), n) / glm::dot(n, n);
							float DY = glm::dot(glm::cross(AToPlayerDist, AC), n) / glm::dot(n, n);
							float DZ = 1 - DX - DY;
							if ((DX >= 0) && (DX <= 1) && (DY >= 0) && (DY <= 1) && (DZ >= 0) && (DZ <= 1))
							{
								getWorld().data.renderUtil->DrawTriangle(A, B, C, Color::Red);
								float Pen = radius - dist;
								getWorld().getEventManager().emitEvent<ParticleContactEvent>(e2, e.getComponent<TriangleComponent>().TriangleA, 0.5f, Trig.Normal, Pen);
								getWorld().getEventManager().emitEvent<ParticleContactEvent>(e2, e.getComponent<TriangleComponent>().TriangleB, 0.5f, Trig.Normal, Pen);
								getWorld().getEventManager().emitEvent<ParticleContactEvent>(e2, e.getComponent<TriangleComponent>().TriangleC, 0.5f, Trig.Normal, Pen);
							}

						}

					}
				}
			}


		}
	}

	void TriangleSystem::CheckCollision(ECSEntity PlaneEntity, ECSEntity sphereEntity)
	{
		

	}
}
