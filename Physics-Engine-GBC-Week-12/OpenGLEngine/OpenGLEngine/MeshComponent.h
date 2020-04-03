#pragma once
namespace Reality
{
	struct ModelComponent
	{		
		// Path to mesh
		std::string mesh;
		// Model ID
		int modelId;
		// HACK : Offset from Transform
		Vector3 offset;
		Vector3 rotation;
		// Constructor
		ModelComponent(std::string const _model = "", Vector3 _rotation = Vector3(0, 0, 0), Vector3 _offset = Vector3(0, 0, 0)) : mesh(_model), offset(_offset), rotation(_rotation)
		{
			modelId = -1;
			Vector3 rotInRads = Vector3(glm::radians(_rotation.x), glm::radians(_rotation.y), glm::radians(_rotation.z));
			modelOffsetTransformation = Mat4(Quaternion(rotInRads));
			modelOffsetTransformation = glm::translate(Mat4(1.0f), _offset) * modelOffsetTransformation;
		}

		const Mat4& GetModelOffsetTransformation()
		{
			return modelOffsetTransformation;
		}

	private:
		Mat4 modelOffsetTransformation;
	};
}
