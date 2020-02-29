#pragma once
#include "ECSConfig.h"
#include "TriangleComponent.h"

namespace Reality
{
	class TriangleSystem : public ECSSystem
	{
	public:
		TriangleSystem();
		void Update(float deltaTime);

		void setPlayerEntity(ECSEntity entity)
		{
			player = entity;
		}
	private:
		ECSEntity player; // Ref to the player (or ball here) that will be checked against the triangles

		float SignedDistanceFromPlane(Vector3 plane, Vector3 planeCenter, Vector3 position);
		bool InsideTriangle(TriangleComponent tri, Vector3 plane, Vector3 position);
		bool SameSide(Vector3 p1, Vector3 p2, Vector3 p3, Vector3 p4);
	};
}
