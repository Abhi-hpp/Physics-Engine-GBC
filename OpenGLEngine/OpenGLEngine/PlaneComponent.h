#pragma once
#include "ECSConfig.h"
#include "TriangleComponent.h"

namespace Reality
{
	struct PlaneComponent
	{
		PlaneComponent(TriangleComponent _Triangle1 = TriangleComponent(), TriangleComponent _Triangle2 = TriangleComponent()):
			Triangle1(_Triangle1), 
			Triangle2(_Triangle2) 
		{

		}

		TriangleComponent Triangle1;
		TriangleComponent Triangle2;
		
	};


}
