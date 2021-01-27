#include "PlaneSystem.h"
#include "TransformComponent.h"
#include "ParticleSphereComponent.h"
#include "ParticleContactEvent.h"
#include "ParticleComponent.h"
#include "ForceAccumulatorComponent.h"
#include "GravityForceComponent.h"

namespace Reality
{
	PlaneSystem::PlaneSystem()
	{

	}

	//Find the plane entities, and compare each individually to the spheres	
	void PlaneSystem::Update(float deltaTime)
	{
		if (glfwGetKey(getWorld().data.renderUtil->window->glfwWindow, GLFW_KEY_E) == GLFW_PRESS)
		{
			for (auto e2 : getEntities())
			{
				if (e2.hasComponent<ParticleSphereComponent>()) // True = Entity has a Sphere
				{
					e2.kill();
				}
			}

			auto sphere = getWorld().createEntity();
			sphere.addComponent<TransformComponent>(Vector3(-15, 12, 2));
			sphere.addComponent<ParticleComponent>();
			sphere.addComponent<ForceAccumulatorComponent>(1.0f);
			sphere.addComponent<GravityForceComponent>();
			sphere.addComponent<ParticleSphereComponent>();
		}
		if (glfwGetKey(getWorld().data.renderUtil->window->glfwWindow, GLFW_KEY_R) == GLFW_PRESS)
		{
			for (auto e2 : getEntities())
			{
				if (e2.hasComponent<ParticleSphereComponent>()) // True = Entity has a Sphere
				{
					e2.kill();
				}
			}

			auto sphere = getWorld().createEntity();
			sphere.addComponent<TransformComponent>(Vector3(15, 12, -2));
			sphere.addComponent<ParticleComponent>();
			sphere.addComponent<ForceAccumulatorComponent>(1.0f);
			sphere.addComponent<GravityForceComponent>();
			sphere.addComponent<ParticleSphereComponent>();
		}		
		for (auto e : getEntities())
		{				
			if (e.hasComponent<PlaneComponent>()) // True = Entity has a Plane
			{				
				auto& plane = e.getComponent<PlaneComponent>();
				bool hasCollided = false;

				if (plane.entityA.hasComponent<TransformComponent>() &&
					plane.entityB.hasComponent<TransformComponent>() &&
					plane.entityC.hasComponent<TransformComponent>())
				{
					auto& transformA = plane.entityA.getComponent<TransformComponent>();
					auto& transformB = plane.entityB.getComponent<TransformComponent>();
					auto& transformC = plane.entityC.getComponent<TransformComponent>();								

					//Step 1: Calculate the plane equation, normal
					Vector3	v1 = transformB.position - transformA.position; // AB
					Vector3	v2 = transformC.position - transformA.position; // AC
					Vector4 norm = Vector4(glm::cross(v1, v2), 0.0f); // Leave space for D of Plane Equation
					norm.w = // Substitute point entity A to solve for D
						-(norm.x * transformA.position.x)
						- (norm.y * transformA.position.y)
						- (norm.z * transformA.position.z);
					for (auto e2 : getEntities())
					{
						if (e2.hasComponent<ParticleSphereComponent>()) // True = Entity has a Sphere
						{
							auto& sphere = e2.getComponent<ParticleSphereComponent>();
							if (e2.hasComponent<TransformComponent>())
							{								
								auto& sphereTransform = e2.getComponent<TransformComponent>();
								//Step 2: Calculate nearest possible point on plane
								//	2A: length of normal to sphere center
								float d = glm::dot(glm::normalize(Vector3(norm)), sphereTransform.position - transformA.position);
								//	2B: find point
								Vector3 point = glm::normalize(Vector3(norm)) * (-d) + sphereTransform.position;

								//getWorld().data.renderUtil->DrawSphere(point, 0.5f, Color::Blue); // Renders nearest point on plane
								//Step 3: Find distance 
								float dist = glm::distance(point, sphereTransform.position);
								if (dist < sphere.radius)
								{									
									//Step 4: Determine if point is within triangle
									// TODO: Find closest points/vertices and try and find closest point to 'point' if this next step fails
									//		This would catch side-collisions
									float A = Area(transformA.position, transformB.position, transformC.position);
									float A1 = Area(point, transformB.position, transformC.position);
									float A2 = Area(transformA.position, point, transformC.position);
									float A3 = Area(transformA.position, transformB.position, point);								

									if (abs(A - A1 - A2 - A3) < 0.001f)	// Within triangle									
									{										
										// Collision
										float penetration = sphere.radius - dist;

										/*getWorld().getEventManager().emitEvent<ParticleContactEvent>(
											e2,
											e,
											0.5f,
											glm::normalize(Vector3(norm)),
											penetration);*/

										getWorld().getEventManager().emitEvent<ParticleContactEvent>(
											e2,
											plane.entityA,
											1.0f,
											glm::normalize(Vector3(norm)),
											penetration);

										getWorld().getEventManager().emitEvent<ParticleContactEvent>(
											e2,
											plane.entityB,
											1.0f,
											glm::normalize(Vector3(norm)),
											penetration);

										getWorld().getEventManager().emitEvent<ParticleContactEvent>(
											e2,
											plane.entityC,
											1.0f,
											glm::normalize(Vector3(norm)),
											penetration);

										getWorld().data.renderUtil->DrawLine(
											sphereTransform.position - Vector3(norm) * sphere.radius,
											sphereTransform.position - Vector3(norm) * (sphere.radius - penetration),
											Color::Red);				

										hasCollided = true;
									}
								}								
							}
						}
					}					
					if (hasCollided)
						getWorld().data.renderUtil->DrawTriangle(transformA.position, transformB.position, transformC.position, Color::Red);
					else {
						getWorld().data.renderUtil->DrawTriangle(transformA.position, transformB.position, transformC.position, Color::Green);
					}
				}				
			}			
		}
	}
	float PlaneSystem::Area(Vector3 p1, Vector3 p2, Vector3 p3)
	{//=ABS(A1*(SQRT(POWER(B2-B3,2)+POWER(C2-C3,2)))+A2*(SQRT(POWER(B3-B1,2)+POWER(C3-C1,2)))+A3*(SQRT(POWER(B1-B2,2)+POWER(C1-C2,2))))				
		Vector3 mid = p2 + (glm::normalize(p3 - p2)) * glm::dot(glm::normalize(p3 - p2), p1 - p2);
		return glm::distance(p3,p2) * glm::distance(p1, mid) * 0.5f;
	}
}		