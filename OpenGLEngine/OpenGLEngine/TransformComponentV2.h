#pragma once
#include "ECSConfig.h"
#include<glm/gtx/quaternion.hpp>


namespace Reality
{
	struct TransformComponentV2
	{
		TransformComponentV2(Vector3 _position = Vector3(0, 0, 0), Vector3 _scale = Vector3(1, 1, 1), Vector3 _eulerAngles = Vector3(0, 0, 0)) :
			position(_position), scale(_scale), eulerAngles(_eulerAngles)
		{

		}
	private:
		Vector3 position;
		Vector3 scale;
		Quaternion orientation;
		Mat4 scaleMatrix;
		Mat4 rotationMatrix;
		Mat4 translationMatrix;
		Mat4 unScaledTransformationMatrix;
		Mat4 transformationMatrix;
		bool dirty = false;

		inline void UpdateMatrices()
		{
			scaleMatrix = glm::scale(Mat4(1.0f), scale);
			rotationMatrix = glm::toMat4(orientation);
			translationMatrix = glm::translate(Mat4(1.0f), position);
			unScaledTransformationMatrix = translationMatrix * rotationMatrix;
			transformationMatrix = unScaledTransformationMatrix * scaleMatrix;
		}

		public:
			inline void SetPosition(Vector3 _position)
			{
				position = _position;
					dirty = true;
			}
			inline Vector3 GetPosition ()
			{
				return position;
			}
	};

}
