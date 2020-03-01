#include "PlaneSystem.h"
#include "TransformComponent.h"
#include "ParticleSphereSystem.h"
#include "ParticleContactEvent.h"

namespace Reality
{
	PlaneSystem::PlaneSystem()
	{
		requireComponent<PlaneComponent>();
	}

	void PlaneSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& plane = e.getComponent<PlaneComponent>();

			Vector3 planep1 = plane.p1.getComponent<TransformComponent>().position;
			Vector3 planep2 = plane.p2.getComponent<TransformComponent>().position;
			Vector3 planep3 = plane.p3.getComponent<TransformComponent>().position;
			Vector3 planep4 = plane.p4.getComponent<TransformComponent>().position;

			plane.normal1 = glm::normalize(glm::cross((planep3 - planep1), (planep2 - planep1)));

			plane.normal2 = glm::normalize(glm::cross((planep3 - planep2), (planep4 - planep2)));


			plane.middle1 = (planep1 + planep2 + planep3) / 3.0f;

			plane.middle2 = (planep2 + planep3 + planep4) / 3.0f;


			plane.d1 = -((plane.normal1.x * plane.middle1.x) + (plane.normal1.y * plane.middle1.y) + (plane.normal1.z * plane.middle1.z));

			plane.d2 = -((plane.normal2.x * plane.middle2.x) + (plane.normal2.y * plane.middle2.y) + (plane.normal2.z * plane.middle2.z));

			float l = (plane.normal1.x * plane.middle1.x) + (plane.normal1.y * plane.middle1.y) + (plane.normal1.z * plane.middle1.z) + plane.d1;

			plane.spheres = getWorld().getSystemManager().getSystem<ParticleSphereSystem>().getEntities();

			for (int i = 0; i < plane.spheres.size(); i++)
			{
				checkCollision(e, plane.spheres[i]);
			}
		}
	}

	void PlaneSystem::checkCollision(ECSEntity _plane, ECSEntity _sphere)
	{
		auto& plane = _plane.getComponent<PlaneComponent>();

		Vector3 planep1 = plane.p1.getComponent<TransformComponent>().position;
		Vector3 planep2 = plane.p2.getComponent<TransformComponent>().position;
		Vector3 planep3 = plane.p3.getComponent<TransformComponent>().position;
		Vector3 planep4 = plane.p4.getComponent<TransformComponent>().position;

		auto& sphere = _sphere.getComponent<ParticleSphereComponent>();
		auto& sphereTransform = _sphere.getComponent<TransformComponent>();

		// Distance = (A*x0+B*y0+C*z0+D) / Sqrt(A*A+B*B+C*C)

		float distance1 = ((plane.normal1.x * sphereTransform.position.x) + (plane.normal1.y * sphereTransform.position.y) + (plane.normal1.z * sphereTransform.position.z) + plane.d1)
			/ sqrt(plane.normal1.x * plane.normal1.x + plane.normal1.y * plane.normal1.y + plane.normal1.z * plane.normal1.z);

		float distance2 = ((plane.normal2.x * sphereTransform.position.x) + (plane.normal2.y * sphereTransform.position.y) + (plane.normal2.z * sphereTransform.position.z) + plane.d2)
			/ sqrt(plane.normal2.x * plane.normal2.x + plane.normal2.y * plane.normal2.y + plane.normal2.z * plane.normal2.z);

		Vector3 projPosition1 = sphereTransform.position - (sphereTransform.position * plane.normal1 / abs(plane.normal1) * abs(plane.normal1)) * plane.normal1;

		Vector3 projPosition2 = sphereTransform.position - (sphereTransform.position * plane.normal2 / abs(plane.normal2) * abs(plane.normal2)) * plane.normal2;

		if (abs(distance1) <= sphere.radius && checkPointInTriangle(projPosition1, planep1, planep2, planep3))
		{
			cout << "Collision" << endl;
			
			float penetration = sphere.radius - abs(distance1);

			getWorld().getEventManager().emitEvent<ParticleContactEvent>(
				_sphere,
				plane.p1,
				1.0f,
				plane.normal1,
				penetration
				);

			getWorld().getEventManager().emitEvent<ParticleContactEvent>(
				_sphere,
				plane.p2,
				1.0f,
				plane.normal1,
				penetration
				);

			getWorld().getEventManager().emitEvent<ParticleContactEvent>(
				_sphere,
				plane.p3,
				1.0f,
				plane.normal1,
				penetration
				);

			getWorld().data.renderUtil->DrawTriangle(planep1, planep2, planep3, Color::Red);
			getWorld().data.renderUtil->DrawTriangle(planep2, planep3, planep4, Color::Green);
		}
		else if (abs(distance2) <= sphere.radius && checkPointInTriangle(projPosition2, planep2, planep3, planep4))
		{
			cout << "Collision" << endl;

			float penetration = sphere.radius - abs(distance2);

			getWorld().getEventManager().emitEvent<ParticleContactEvent>(
				_sphere,
				plane.p2,
				1.0f,
				plane.normal2,
				penetration
				);

			getWorld().getEventManager().emitEvent<ParticleContactEvent>(
				_sphere,
				plane.p3,
				1.0f,
				plane.normal2,
				penetration
				);

			getWorld().getEventManager().emitEvent<ParticleContactEvent>(
				_sphere,
				plane.p4,
				1.0f,
				plane.normal2,
				penetration
				);

			getWorld().data.renderUtil->DrawTriangle(planep2, planep3, planep4, Color::Red);
			getWorld().data.renderUtil->DrawTriangle(planep1, planep2, planep3, Color::Green);
		}
		else
		{
			getWorld().data.renderUtil->DrawTriangle(planep1, planep2, planep3, Color::Green);
			getWorld().data.renderUtil->DrawTriangle(planep2, planep3, planep4, Color::Green);
		}

		if (sphereTransform.position.y <= -20)
		{
			sphereTransform.position = plane.middle1;

			sphereTransform.position.x += RANDOM_FLOAT(-3.0f, 3.0f);
			sphereTransform.position.z += RANDOM_FLOAT(-3.0f, 3.0f);
			sphereTransform.position.y += 20.0f;
		}

		//Vector3 relativeLocation = plane.normal1 - sphereTransform.position;
		//float d = glm::length(relativeLocation);
		//
		//float distance1 = (plane.normal1.x * sphereTransform.position.x) + (plane.normal1.y * sphereTransform.position.y) + (plane.normal1.z * sphereTransform.position.z) - plane.d1;
		//float distance2 = (plane.normal2.x * sphereTransform.position.x) + (plane.normal2.y * sphereTransform.position.y) + (plane.normal2.z * sphereTransform.position.z) - plane.d2;
		//
		//float j = glm::length((sphere.radius - abs(distance1)) * plane.normal1);

		//float temp = sphere.radius - abs(distance);

		//if(p == sphere.radius - abs(glm::distance(sphereTransform.position, plane.middle1) * plane.normal1))

	}

	bool PlaneSystem::checkSameSide(Vector3 p1, Vector3 p2, Vector3 a, Vector3 b)
	{
		Vector3 cp1 = glm::cross(b - a, p1 - a);
		Vector3 cp2 = glm::cross(b - a, p2 - a);

		float d = glm::dot(cp1, cp2);

		if (glm::dot(cp1, cp2) >= 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool PlaneSystem::checkPointInTriangle(Vector3 p, Vector3 a, Vector3 b, Vector3 c)
	{
		if (checkSameSide(p, a, b, c) && checkSameSide(p, b, a, c) && checkSameSide(p, c, a, b))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	/*
	
		function SameSide(p1,p2, a,b)
		    cp1 = CrossProduct(b-a, p1-a)
		    cp2 = CrossProduct(b-a, p2-a)
		    if DotProduct(cp1, cp2) >= 0 then return true
		    else return false
		
		function PointInTriangle(p, a,b,c)
		    if SameSide(p,a, b,c) and SameSide(p,b, a,c)
		        and SameSide(p,c, a,b) then return true
		    else return false
	*/
}
