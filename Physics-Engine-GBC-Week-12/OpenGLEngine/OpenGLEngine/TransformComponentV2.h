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
		bool dirty = true;

		inline void UpdateMatrices()
		{
			scaleMatrix = glm::scale(Mat4(1.0f), scale);
			rotationMatrix = glm::toMat4(orientation);
			translationMatrix = glm::translate(Mat4(1.0f), position);
			unScaledTransformationMatrix = translationMatrix * rotationMatrix;
			transformationMatrix = unScaledTransformationMatrix * scaleMatrix;
			dirty = false;
		}
	public: 

		inline void SetPosition(const Vector3& _position)
		{
			position = _position;
			dirty = true;
		}

		inline const Vector3& GetPosition()
		{
			return position;
		}

		inline void SetScale(const Vector3& _scale)
		{
			scale = _scale;
			dirty = true;
		}

		inline const Vector3& GetScale()
		{
			return scale;
		}

		inline void SetOrientation(const Quaternion& _orientation)
		{
			orientation = _orientation;
			dirty = true;
		}

		inline const Quaternion& GetOrientation()
		{
			return orientation;
		}

		inline void SetEulerAngles(const Vector3& _eulerAngles)
		{
			Vector3 radAngle = Vector3(glm::radians(_eulerAngles.x),
				glm::radians(_eulerAngles.y), glm::radians(_eulerAngles.z));
			orientation = glm::quat(radAngle);
			dirty = true;
		}

		inline const Vector3& GetEulerAngles()
		{
			return glm::eulerAngles(orientation);
		}

		inline const Mat4& GetScaleMatrix()
		{
			if (dirty)
			{
				UpdateMatrices();
			}
			return scaleMatrix;
		}

		inline const Mat4& GetRotationMatrix()
		{
			if (dirty)
			{
				UpdateMatrices();
			}
			return rotationMatrix;
		}

		inline const Mat4& GetTranslationMatrix()
		{
			if (dirty)
			{
				UpdateMatrices();
			}
			return translationMatrix;
		}

		inline const Mat4& GetUnScaledTransformationMatrix()
		{
			if (dirty)
			{
				UpdateMatrices();
			}
			return unScaledTransformationMatrix;
		}

		inline const Mat4& GetTransformationMatrix()
		{
			if (dirty)
			{
				UpdateMatrices();
			}
			return transformationMatrix;
		}

		inline const Vector3& Right()
		{
			return orientation * Vector3(1, 0, 0);
		}

		inline const Vector3& Up()
		{
			return orientation * Vector3(0, 1, 0);
		}

		inline const Vector3& Forward()
		{
			return orientation * Vector3(0, 0, 1);
		}

		inline const Vector3& LocalToWorldDirection(const Vector3& _localDirection)
		{
			return orientation * _localDirection;
		}

		inline const Vector3& WorldToLocalDirection(const Vector3& _worldDirection)
		{
			if (glm::length(orientation) > 0)
			{
				return glm::inverse(orientation) * _worldDirection;
			}
			return Vector3(0, 0, 0);
		}


		inline const Vector3& LocalToWorldPosition(const Vector3& _localPosition)
		{
			return GetTransformationMatrix() * Vector4(_localPosition, 1.0f);
		}

		inline const Vector3& WorldToLocalPosition(const Vector3& _worldPosition)
		{
			if (abs(glm::determinant(GetTransformationMatrix())) > 0)
			{
				return glm::inverse(GetTransformationMatrix()) * Vector4(_worldPosition, 1.0f);
			}
			return Vector3(0, 0, 0);
		}
	};
}
