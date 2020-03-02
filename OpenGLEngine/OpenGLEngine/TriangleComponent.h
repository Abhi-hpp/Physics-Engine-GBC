#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct TriangleComponent
	{
		TriangleComponent(ECSEntity _vertex_1 = ECSEntity(), ECSEntity _vertex_2 = ECSEntity(), ECSEntity _vertex_3 = ECSEntity())
			: vertex_1(_vertex_1), vertex_2(_vertex_2), vertex_3(_vertex_3)
		{

		}

		ECSEntity vertex_1;
		ECSEntity vertex_2;
		ECSEntity vertex_3;

	};
}
