#pragma once
#include "ECSConfig.h"
#include <glm/gtx/quaternion.hpp>

namespace Reality
{
	struct TransformComponentV2
	{
		TransformComponentV2(Vector3 _position = Vector3(0, 0, 0), Vector3 _scale = Vector3(1, 1, 1), Vector3 _eulerAngles = Vector3(0, 0, 0)) :
			position(_position), scale(_scale)
		{
			SetEulerAngles(_eulerAngles);
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

		bool dirty;

		inline void UpdateMatrices()
		{
			scaleMatrix = glm::scale(Mat4(1.0f), scale);
			translationMatrix = glm::translate(Mat4(1.0f), position);
			rotationMatrix = glm::toMat4(orientation);
			unScaledTransformationMatrix = translationMatrix * rotationMatrix;
			transformationMatrix = unScaledTransformationMatrix * scaleMatrix;
			dirty = false;
		}
	public:
		inline void SetPosition(Vector3 _position)
		{
			position = _position;
			dirty = true;
		}
		inline Vector3 GetPosition()
		{
			return position;
		}
		inline void SetScale(Vector3 _scale)
		{
			scale = _scale;
			dirty = true;
		}
		inline Vector3 GetScale()
		{
			return scale;
		}
		inline void SetOrientation(Quaternion _orientation)
		{
			orientation = _orientation;
			dirty = true;
		}
		inline Quaternion GetOrientation()
		{
			return orientation;
		}
		inline void SetEulerAngles(Vector3 _eulerAngle)
		{
			Vector3 eulerRads = Vector3(glm::radians(_eulerAngle.x), glm::radians(_eulerAngle.y), glm::radians(_eulerAngle.z));
			orientation = glm::quat(eulerRads);
			dirty = true;
		}
		inline Vector3 GetEulerAngles()
		{
			return glm::eulerAngles(orientation);
		}
		inline Mat4 GetScaleMatrix()
		{
			if (dirty == true)
			{
				UpdateMatrices();
			}
			return scaleMatrix;
		}
		inline Mat4 GetTranslationMatrix()
		{
			if (dirty == true)
			{
				UpdateMatrices();
			}
			return translationMatrix;
		}
		inline Mat4 GetRotationMatrix()
		{
			if (dirty == true)
			{
				UpdateMatrices();
			}
			return rotationMatrix;
		}
		inline Mat4 GetUnScaleTransformationMatrix()
		{
			if (dirty == true)
			{
				UpdateMatrices();
			}
			return unScaledTransformationMatrix;
		}
		inline Mat4 GetTransformationMatrix()
		{
			if (dirty == true)
			{
				UpdateMatrices();
			}
			return transformationMatrix;
		}
		inline Vector3 Right()
		{
			return orientation * Vector3(1.0f, 0.0f, 0.0f);
		}
		inline Vector3 Up()
		{
			return orientation * Vector3(0.0f, 1.0f, 0.0f);
		}
		inline Vector3 Forward()
		{
			return orientation * Vector3(0.0f, 0.0f, 1.0f);
		}
		inline Vector3 LocaltoWorldPosition(Vector3 localPosition)
		{
			return transformationMatrix * Vector4(localPosition, 1.0f);
		}
		inline Vector3 WorldToLocalPosition(Vector3 worldPosition)
		{
			if (abs(glm::determinant(transformationMatrix)) > 0)
			{
				return glm::inverse(transformationMatrix) * Vector4(worldPosition, 1.0f);
			}
			return Vector3(0, 0, 0);
		}
		inline Vector3 LocaltoWorldDirection(Vector3 localDirection)
		{
			return orientation * localDirection;
		}
		inline Vector3 WorldToLocalDirection(Vector3 worldDirection)
		{
			if (glm::length(orientation) > 0)
			{
				return glm::inverse(orientation) * worldDirection;
			}
			return Vector3(0, 0, 0);
		}
	};
}
