#pragma once
#include "ECSConfig.h"
namespace Reality
{
	struct TransformComponent
	{
		TransformComponent(Vector3 _position = Vector3(0, 0, 0), Vector3 _scale = Vector3(1,1,1), Vector3 _eulerAngles = Vector3(0,0,0)) :
			position(_position), scale(_scale), eulerAngles(_eulerAngles)
		{

		}
		Vector3 position;
		Vector3 scale;
		Vector3 eulerAngles;
		Quaternion orientation;
		Mat4 scaleMatrix;
		Mat4 rotationMatrix;
		Mat4 translationMatrix;
		Mat4 unScaledTransformationMatrix;
		Mat4 transformationMatrix;
	};
}