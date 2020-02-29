#pragma once
#include "ECSConfig.h"
#include <glm/gtx/quaternion.hpp>

namespace Reality
{
	struct TransformComponentV2
	{
		TransformComponentV2(Vector3 _position = Vector3(0, 0, 0), Vector3 _scale = Vector3(1, 1, 1), Vector3 _eulerAngles = Vector3(0.0f, 0.0f, 0.0f)) :
			position(_position), scale(_scale)
		{
			SetRotation(_eulerAngles);
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
			scaleMatrix = glm::scale(glm::mat4(1.0f), scale);
			translationMatrix = glm::translate(glm::mat4(1.0f), position);
			rotationMatrix = glm::toMat4(orientation);
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

		inline Vector3 GetPosition() { return position; }

		inline void SetScale(const Vector3& _scale)
		{
			scale = _scale;
			dirty = true;
		}

		inline Vector3 GetScale() { return scale; }

		inline void SetOrientation(const Quaternion& _orientation)
		{
			orientation = _orientation;
			dirty = true;
		}

		inline Quaternion GetOrientation() { return orientation; }

		// Euler angles in degrees
		inline void SetRotation(Vector3 eulerAngles)
		{
			glm::vec3 rotationInRads = glm::vec3(glm::radians(eulerAngles.x), 
				glm::radians(eulerAngles.y), glm::radians(eulerAngles.z));
			orientation = glm::quat(rotationInRads);
			dirty = true;
		}

		inline Vector3 GetRotation() { return glm::eulerAngles(orientation); }

		inline Vector3 Up()
		{
			return orientation * Vector3(0.0f, 1.0f, 0.0f);
		}

		inline Vector3 Right()
		{
			return orientation * Vector3(1.0f, 0.0f, 0.0f);
		}

		inline Vector3 Forward()
		{
			return orientation * Vector3(0.0f, 0.0f, 1.0f);
		}

		inline Mat4 GetScaleMatrix()
		{
			if (dirty)
			{
				UpdateMatrices();
			}
			return scaleMatrix;
		}

		inline Mat4 GetRotationMatrix()
		{
			if (dirty)
			{
				UpdateMatrices();
			}
			return rotationMatrix;
		}

		inline Mat4 GetTranslationMatrix()
		{
			if (dirty)
			{
				UpdateMatrices();
			}
			return transformationMatrix;
		}

		inline Mat4 GetUnScaledTransformationMatrix()
		{
			if (dirty)
			{
				UpdateMatrices();
			}
			return unScaledTransformationMatrix;
		}

		inline Mat4 GetTransformationMatrix()
		{
			if (dirty)
			{
				UpdateMatrices();
			}
			return transformationMatrix;
		}

		inline Vector3 WorldToLocalPosition(Vector3 _position)
		{
			return glm::inverse(GetTransformationMatrix()) * Vector4(_position, 1);

		}

		inline Vector3 LocalToWorldPosition(Vector3 _position)
		{
			return GetTransformationMatrix() * Vector4(_position, 1);
		}

		//TODO : Check
		inline Vector3 WorldToLocalDirection(Vector3 direction)
		{
			if (glm::length(orientation) > 0)
			{
				return glm::inverse(orientation) * direction;
			}
			return Vector3(0, 0, 0);
		}

		inline Vector3 LocalToWorldDirection(Vector3 direction)
		{
			return orientation * direction;
		}
	};
}
