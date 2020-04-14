#pragma once
struct RotateComponent
{
	float xRot;
	float yRot;
	float zRot;
	RotateComponent(float x = 0, float y = 0, float z = 0)
		: xRot(x), yRot(y), zRot(z) {}
};
