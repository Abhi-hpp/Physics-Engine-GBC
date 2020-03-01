#pragma once
#include "ECSConfig.h"
#include "TriangleComponent.h"
#include "TransformComponent.h"

namespace Reality
{
	class TriangleSystem : public ECSSystem
	{
	private:
		static ECSEntity player;
		static bool createPlayer;
		Vector3 cross;
		Vector3 crossNormalized;
		Vector3 avg;
		Vector3 pos;
		ECSEntity e1;
		ECSEntity e2;
		ECSEntity e3;
		Vector3 e1Pos;
		Vector3 e2Pos;
		Vector3 e3Pos;
		float distance;
		float d;
		float D;
		Vector4 plane;
		Vector4 planeNormalized;

	public:
		TriangleSystem();
		void makePlayer();
		bool isInside(Vector3 p1, Vector3 p2, Vector3 p3, Vector3 spherePos);
		void Update(float deltaTime);

		static bool getCreatePlayer() { return createPlayer; }
		static void setCreatePlayer(bool _createPlayer) { createPlayer = _createPlayer; }
		static ECSEntity *getPlayer() { return &player; }
	};
}
