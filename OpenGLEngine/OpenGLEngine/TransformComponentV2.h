#pragma once
#include "ECSConfig.h"
#include <glm/gtx/quaternion.hpp>

namespace Reality
{
	struct TransformComponentV2
	{
<<<<<<< Updated upstream
		TransformComponentV2(Vector3 _position = Vector3(0, 0, 0), Vector3 _scale = Vector3(1, 1, 1), Vector3 _eulerAngles = Vector3(0.0f, 0.0f, 0.0f)) :
			position(_position), scale(_scale)
		{
			SetRotation(_eulerAngles);
=======
		TransformComponentV2(Vector3 _position = Vector3(0, 0, 0), Vector3 _scale = Vector3(1, 1, 1), Vector3 _eulerAngles = Vector3(0, 0, 0)) :
			position(_position), scale(_scale)
		{
			SetEulerAngles(_eulerAngles);
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
			scaleMatrix = glm::scale(glm::mat4(1.0f), scale);
			translationMatrix = glm::translate(glm::mat4(1.0f), position);
			rotationMatrix = glm::toMat4(orientation);
=======
			scaleMatrix = glm::scale(Mat4(1.0f), scale);
			rotationMatrix = glm::toMat4(orientation);
			translationMatrix = glm::translate(Mat4(1.0f), position);
>>>>>>> Stashed changes
			unScaledTransformationMatrix = translationMatrix * rotationMatrix;
			transformationMatrix = unScaledTransformationMatrix * scaleMatrix;
			dirty = false;
		}
<<<<<<< Updated upstream

	public:
=======
	public: 

>>>>>>> Stashed changes
		inline void SetPosition(const Vector3& _position)
		{
			position = _position;
			dirty = true;
		}

<<<<<<< Updated upstream
		inline Vector3 GetPosition() { return position; }
=======
		inline const Vector3& GetPosition()
		{
			return position;
		}
>>>>>>> Stashed changes

		inline void SetScale(const Vector3& _scale)
		{
			scale = _scale;
			dirty = true;
		}

<<<<<<< Updated upstream
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
=======
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
>>>>>>> Stashed changes
		{
			if (dirty)
			{
				UpdateMatrices();
			}
			return scaleMatrix;
		}

<<<<<<< Updated upstream
		inline Mat4 GetRotationMatrix()
=======
		inline const Mat4& GetRotationMatrix()
>>>>>>> Stashed changes
		{
			if (dirty)
			{
				UpdateMatrices();
			}
			return rotationMatrix;
		}

<<<<<<< Updated upstream
		inline Mat4 GetTranslationMatrix()
=======
		inline const Mat4& GetTranslationMatrix()
>>>>>>> Stashed changes
		{
			if (dirty)
			{
				UpdateMatrices();
			}
<<<<<<< Updated upstream
			return transformationMatrix;
		}

		inline Mat4 GetUnScaledTransformationMatrix()
=======
			return translationMatrix;
		}

		inline const Mat4& GetUnScaledTransformationMatrix()
>>>>>>> Stashed changes
		{
			if (dirty)
			{
				UpdateMatrices();
			}
			return unScaledTransformationMatrix;
		}

<<<<<<< Updated upstream
		inline Mat4 GetTransformationMatrix()
=======
		inline const Mat4& GetTransformationMatrix()
>>>>>>> Stashed changes
		{
			if (dirty)
			{
				UpdateMatrices();
			}
			return transformationMatrix;
		}

<<<<<<< Updated upstream
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
=======
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
>>>>>>> Stashed changes
			}
			return Vector3(0, 0, 0);
		}

<<<<<<< Updated upstream
		inline Vector3 LocalToWorldDirection(Vector3 direction)
		{
			return orientation * direction;
=======

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
>>>>>>> Stashed changes
		}
	};
}
