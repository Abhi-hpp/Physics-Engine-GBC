#pragma once
#include <glad/glad.h> // holds all OpenGL type declarations

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "Material.h"
#include "Camera.h"


using namespace std;
struct Vertex {
	// position
	glm::vec3 Position;
	// normal
	glm::vec3 Normal;
	// texCoords
	glm::vec2 TexCoords;
	// tangent
	glm::vec3 Tangent;
	// bitangent
	glm::vec3 Bitangent;
};

namespace Reality
{
	class Model;
	class Mesh {
	public:
		/*  Mesh Data  */
		Model* model;
		vector<Vertex> vertices;
		vector<unsigned int> indices;
		int materialIndex;
		string name;
		bool dirty;
		unsigned int VAO;
		/*  Functions  */
		// constructor
		Mesh(Model* _model, int _materialIndex, string _name = "Mesh");

		/*  Functions    */
		// initializes all the buffer objects/arrays
		void Init();

		// render the mesh
		void Draw();

	private:
		/*  Render data  */
		unsigned int VBO, EBO;	
	};
}