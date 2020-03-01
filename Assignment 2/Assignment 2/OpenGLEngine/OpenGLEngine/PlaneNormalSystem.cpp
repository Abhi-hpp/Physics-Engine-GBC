#include "PlaneNormalSystem.h"
#include "GravityForceComponent.h"
#include "ParticleContactEvent.h"
#include "ParticleSphereComponent.h"

namespace Reality
{
	PlaneNormalSystem::PlaneNormalSystem()
	{
		requireComponent<PlaneNormalComponent>();
		//requireComponent<ForceAccumulatorComponent>();
	}

	void PlaneNormalSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& plane= e.getComponent<PlaneNormalComponent>();

			if (plane.entityA.hasComponent<TransformComponent>() &&
				plane.entityB.hasComponent<TransformComponent>() &&
				plane.entityC.hasComponent<TransformComponent>() &&
				plane.entityD.hasComponent<TransformComponent>())
			{
				auto& transformA = plane.entityA.getComponent<TransformComponent>();
				auto& transformB = plane.entityB.getComponent<TransformComponent>();
				auto& transformC = plane.entityC.getComponent<TransformComponent>();
				auto& transformD = plane.entityD.getComponent<TransformComponent>();

				auto& sphere = plane.entityD.getComponent<ParticleSphereComponent>();
				/*auto& forceA = plane.entityA.getComponent<ForceAccumulatorComponent>();
				auto& forceB = plane.entityB.getComponent<ForceAccumulatorComponent>();
				auto& forceC = plane.entityC.getComponent<ForceAccumulatorComponent>();
				*/
				Vector3 AB = transformB.position - transformA.position;
				Vector3 AC = transformC.position - transformA.position;

				plane.Normals.x = (AB.y * AC.z) - (AB.z * AC.y);
				plane.Normals.y = -(AB.x * AC.z) - (AB.z * AC.x);
				plane.Normals.z = (AB.x * AC.y) - (AB.y * AC.x);
				plane.magnitude = glm::sqrt(plane.Normals.x * plane.Normals.x + plane.Normals.y * plane.Normals.y + plane.Normals.z * plane.Normals.z);

				//normals.x = normals.x / magnitude;
				//normals.y = normals.y / magnitude;
				//normals.z = normals.z / magnitude;
				plane.planeDist = plane.Normals.x * (transformB.position.x - transformA.position.x) + 
					plane.Normals.y * (transformB.position.y - transformA.position.y) + 
					plane.Normals.z * (transformB.position.z - transformA.position.z);

			
				/*
				transformD.position.y - sphere.radius <= 2 &&
					(transformD.position.x - sphere.radius >= -7 && abs(transformD.position.x) + sphere.radius <= 13) &&
					(transformD.position.z - sphere.radius >= -5 && abs(transformD.position.z) + sphere.radius <= 5)
				*/

				float distance = (plane.Normals.x * transformD.position.x) + (plane.Normals.y * transformD.position.y) + (plane.Normals.z * transformD.position.z);
				if (abs(distance) + sphere.radius <= abs(plane.planeDist) && distance - sphere.radius >= plane.planeDist)
				{
					cout << "Distance : " << distance << "PlaneDist : " << plane.planeDist << endl;

					getWorld().data.renderUtil->DrawTriangle(
						transformA.position,
						transformB.position,
						transformC.position,
						Color::Magenta
					);


					float penetration = 0.0;

					getWorld().getEventManager().emitEvent<ParticleContactEvent>(
						plane.entityD,
						plane.entityC,
						0.5f,
						plane.Normals / plane.magnitude,
						penetration
						);
					getWorld().getEventManager().emitEvent<ParticleContactEvent>(
						plane.entityD,
						plane.entityB,
						0.5f,
						plane.Normals / plane.magnitude,
						penetration
						);
					getWorld().getEventManager().emitEvent<ParticleContactEvent>(
						plane.entityD,
						plane.entityA,
						0.5f,
						plane.Normals / plane.magnitude,
						penetration
						);
				}

				else
				{
					getWorld().data.renderUtil->DrawTriangle(
					transformA.position,
					transformB.position,
					transformC.position,
					Color::Green
				);
				}
			}


		}
	}
}
