#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct TriangleComponent
	{
		TriangleComponent(ECSEntity _vertexA = ECSEntity(), ECSEntity _vertexB = ECSEntity(), ECSEntity _vertexC = ECSEntity(), ECSEntity _sphere = ECSEntity()) 
			: vertexA(_vertexA), vertexB(_vertexB), vertexC(_vertexC), sphere(_sphere)
		{

		}
		ECSEntity vertexA;
		ECSEntity vertexB;
		ECSEntity vertexC;

		ECSEntity sphere;
	};
}
