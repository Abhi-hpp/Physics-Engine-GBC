#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct AeroMinMaxComponent
	{
		AeroMinMaxComponent(Mat3 _minTensor = Mat3(1.0f), Mat3 _baseTensor = Mat3(1.0f), Mat3 _maxTensor = Mat3(1.0f), float _controlSetting = 0.0f)
			:minTensor(_minTensor), baseTensor(_baseTensor), maxTensor(_maxTensor), controlSetting(_controlSetting)
		{

		}
		Mat3 minTensor;
		Mat3 baseTensor;
		Mat3 maxTensor;
		float controlSetting;
	};
}
