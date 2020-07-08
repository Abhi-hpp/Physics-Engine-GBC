#include "TriangleCollisionSystem.h"
#include "TransformComponent.h"
#include "ParticleComponent.h"
#include "ForceAccumulatorComponent.h"
#include "GravityForceComponent.h"
#include "PenetrationDeltaMoveComponent.h"
#include "ParticleContactEvent.h"

namespace Reality
{
	TriangleCollisionSystem::TriangleCollisionSystem()
	{
		requireComponent<TriangleCollisionComponent>();
	}

	void TriangleCollisionSystem::Update(float deltaTime)
	{
		if (ballMade == false)
		{
			ball = getWorld().createEntity();
			ball.addComponent<TransformComponent>(Vector3(15, 10, 0));
			ball.addComponent<ParticleComponent>();
			ball.addComponent<ForceAccumulatorComponent>(1.0f);
			ball.addComponent<GravityForceComponent>();
			ball.addComponent<PenetrationDeltaMoveComponent>();
			ballMade = true;
		}
		
		for (auto e : getEntities())
		{

			auto& triangle = e.getComponent<TriangleCollisionComponent>();

			// Grab Triangle Points
			Vector3 triP1 = triangle.p1.getComponent<TransformComponent>().position;
			Vector3 triP2 = triangle.p2.getComponent<TransformComponent>().position;
			Vector3 triP3 = triangle.p3.getComponent<TransformComponent>().position;

			// Draw Triangles in a nice wood color
			// getWorld().data.renderUtil->DrawTriangle(triP1, triP2, triP3, Color(0.64, 0.24, 0.16, 1));


			// Find the Normal
			Vector3 v1 = triP2 - triP1;
			Vector3 v2 = triP3 - triP1;
			Vector3 triNormal = glm::normalize(glm::cross(v1, v2));

			// Draw the normal from the centre of Triangle
			Vector3 triCentre = (triP1 + triP2 + triP3) / 3.0f;
			getWorld().data.renderUtil->DrawLine(triCentre, triCentre + (triNormal), Color(1, 0, 0, 1));

			// Find the D coordinate of Triangle Normal
			float triPlaneD = -(triNormal.x * triCentre.x + triNormal.y * triCentre.y + triNormal.z * triCentre.z);

			// Add the D coordinate to the Triangle Normal to convert from Vector3 to Vector4
			Vector4 triPlane = Vector4(triNormal, triPlaneD);


			Vector4 spherePos = Vector4(ball.getComponent<TransformComponent>().position, 1);
			float distance = glm::dot(triPlane, spherePos);
			
			//Barycentric Coordinates of a Projected Point

			// u = p2 - p1
			Vector3 u = triP2 - triP1;
			// v = p3 - p1
			Vector3 v = triP3 - triP1;
			// n = u × v
			Vector3 n = glm::cross(u, v);
			// w = ball − p1
			Vector3 w = ball.getComponent<TransformComponent>().position - triP1;

			// Barycentric coordinates of the projection P′(projected point) of P(sphere) onto T(plane):
			
			float gamma = glm::dot(glm::cross(u, w), n) / glm::dot(n, n);
			float beta = glm::dot(glm::cross(w, v), n) / glm::dot(n, n);
			float alpha = 1 - gamma - beta;

			// The point P′ lies inside T if:
			if (((0 <= alpha) && (alpha <= 1) && (0 <= beta) && (beta <= 1) && (0 <= gamma) && (gamma <= 1)))
			{
				if (abs(distance) < 1)
				{
					float penetration = 1 - distance;

					getWorld().getEventManager().emitEvent<ParticleContactEvent>(triangle.p1,ball,0.8f,-triNormal,penetration);
					getWorld().getEventManager().emitEvent<ParticleContactEvent>(triangle.p2,ball,0.8f,-triNormal,penetration);
					getWorld().getEventManager().emitEvent<ParticleContactEvent>(triangle.p3,ball,0.8f,-triNormal,penetration);
				}
				getWorld().data.renderUtil->DrawTriangle(triP1, triP2, triP3, Color(0, 0, 1, 1));
			}
			else {
				// Nice woody color
				getWorld().data.renderUtil->DrawTriangle(triP1, triP2, triP3, Color(0.64, 0.24, 0.16, 1));
			}
		}
		
	}
	void TriangleCollisionSystem::GenerateBall()
	{
		ball.addComponent<TransformComponent>(Vector3(RANDOM_FLOAT(-13,15), 10, 0));
		ball.addComponent<ParticleComponent>();
		ball.addComponent<ForceAccumulatorComponent>(1.0f);
		ball.addComponent<GravityForceComponent>();
		ball.addComponent<PenetrationDeltaMoveComponent>();
	}
}
