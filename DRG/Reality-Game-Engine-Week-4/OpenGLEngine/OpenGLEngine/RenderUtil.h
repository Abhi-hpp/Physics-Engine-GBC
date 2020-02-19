#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <map>
#include <unordered_map>
// FreeType
#include <ft2build.h>
#include FT_FREETYPE_H
#include "AssetLoader.h"
#include "Model.h"
#include "Shader.h"
#include "Camera.h"
#include "Window.h"
#include "Color.h"
#define MAX_DIR_LIGHTS 100
#define MAX_POINT_LIGHTS 100
#define MAX_SPOT_LIGHTS 100

class Shader;
namespace Reality
{
	struct Character {
		GLuint TextureID;   // ID handle of the glyph texture
		glm::ivec2 Size;    // Size of glyph
		glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
		GLuint Advance;    // Horizontal offset to advance to next glyph
	};

	struct DirLight {
		glm::vec4 direction;
		glm::vec4 ambient;
		glm::vec4 diffuse;
		glm::vec4 specular;
	};

	struct PointLight {
		glm::vec4 position;
		glm::vec4 ambient;
		glm::vec4 diffuse;
		glm::vec4 specular;
		float constant;
		float linear;
		float quadratic;
		float padding;
	};

	struct SpotLight {
		glm::vec4 position;
		glm::vec4 direction;
		glm::vec4 ambient;
		glm::vec4 diffuse;
		glm::vec4 specular;
		float cutOff;
		float outerCutOff;
		float constant;
		float linear;
		float quadratic;
		float padding1;
		float padding2;
		float padding3;
	};

	class RenderUtil
	{
	public:
		RenderUtil(const std::shared_ptr<Reality::AssetLoader> _assetLoader);
		/*Initialization*/
		GLFWwindow* InitWindow(int width, int height, const char* title);

		/*Draw*/
		void DrawModel(int modelID, const glm::vec3& position = glm::vec3(0, 0, 0), const glm::vec3& scale = glm::vec3(1, 1, 1), const glm::vec3& rotation = glm::vec3(0, 0, 0), unsigned int drawMode = GL_FILL);
		void DrawModel(int modelID, glm::mat4 modelMatrix = glm::mat4(1.0f), unsigned int drawMode = GL_FILL);


		/*Draw Primitives*/
		void DrawSphere(const glm::vec3& position = glm::vec3(0, 0, 0), float radius = 1, const Color& color = Color(0, 1, 0, 1));
		void DrawCube(const glm::vec3& position = glm::vec3(0,0,0), const glm::vec3& scale = glm::vec3(1, 1, 1), const glm::vec3& rotation = glm::vec3(0, 0, 0), const Color& color = Color(0,1,0,1));
		void DrawCube(const glm::vec3& position, const glm::vec3& scale, const glm::quat& orientation, const Color& color = Color(0, 1, 0, 1));
		void DrawLine(const glm::vec3& start, const glm::vec3& end, const Color& color = Color(0, 1, 0, 1));
		void DrawTriangle(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c, const Color& color = Color(0, 1, 0, 1));

		/*TextRender*/
		void RenderText(std::string text, float x, float y, float scale, Color color);

		/*Window Utils*/
		void ClearDisplay(GLFWwindow* window);
		void SwapBuffers(GLFWwindow* window);

		/*Buffer Utils*/
		void SetFOV(float fov);
		void UpdateViewMatrix();

		/*Lights*/
		void UpdateDirLights(const std::vector<DirLight>& lightArray, int numLights);
		void UpdatePointLights(const std::vector<PointLight>& lightArray, int numLights);
		void UpdateSpotLights(const std::vector<SpotLight>& lightArray, int numLights);

		/*Camera And Window*/
		Camera camera;
		std::unique_ptr<Window> window;

		inline int GetVerts() { return verts; }
		inline int GetTris() { return triangles; }
		inline int GetLines() { return lines; }
		inline int GetDrawCalls() { return drawCalls; }
		inline float GetRenderDelta() { return renderDeltaTime; }

	private:
		/*Pointer to asset loader*/
		std::shared_ptr<Reality::AssetLoader> assetLoader;

		/*Caches*/
		std::map<GLchar, Character> Characters;

		/*Uniform Buffers*/
		unsigned int uboMatrices;
		unsigned int uboDirectionalLights;
		unsigned int uboPointLights;
		unsigned int uboSpotLights;
		void SetupUBOs();

		/*Buffer Utils*/
		void SetModelTransform(const glm::mat4 model = glm::mat4(1.0f));
		void SetModelTransform(const glm::vec3& position = glm::vec3(0, 0, 0), const glm::vec3& scale = glm::vec3(1, 1, 1), const glm::vec3& rotation = glm::vec3(0, 0, 0));
		void SetModelTransform(const glm::vec3& position, const glm::vec3& scale, const glm::quat& orientation);

		/*Primitive Buffers and Shaders*/
		unsigned int cubeVBO, cubeVAO;
		unsigned int sphereVBO, sphereIBO, sphereVAO, numIndices;
		unsigned int lineVBO, lineVAO;
		unsigned int triangleVBO, triangleVAO;
		GLuint textVAO, textVBO;
		Material primitiveShader = Material(new Shader("Shaders/vertexDefault.vs", "Shaders/FragmentConstant.fs"));
		Material primitiveShaderBasic = Material(new Shader("Shaders/SimpleVertex.vs", "Shaders/FragmentConstant.fs"));
		Material textShader = Material(new Shader("Shaders/text.vs", "Shaders/text.fs"));

		/*Set Up Primitives*/
		void SetupPrimitives();
		void SetUpPrimitiveShaders();
		void SetUpCubePrimitive();
		void SetUpSpherePrimitive();
		void SetUpLinePrimitive();
		void SetupTrianglePrimitive();
		void SetupTextRender();

		/*Debug*/
		int verts;
		int triangles;
		int lines;
		int drawCalls;
		float renderDeltaTime;
	};
}

