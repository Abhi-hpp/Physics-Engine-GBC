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
		ModelComponent(std::string const _model = "", Vector3 _offset = Vector3(0, 0, 0), Vector3 _rotation = Vector3(0, 0, 0)) : mesh(_model), offset(_offset), rotation(_rotation)
		{
			modelId = -1;
		}
	};
}
