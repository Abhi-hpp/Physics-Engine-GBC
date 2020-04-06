#pragma once
namespace Reality
{
	struct FPSControlComponent
	{
		FPSControlComponent()
		{}
		float forwardSpeed = 10;
		float sidewaysSpeed = 10;
		float cameraXSpeed = 1;
		float cameraYSpeed = 1;
		bool inverted = false;
	};
}
