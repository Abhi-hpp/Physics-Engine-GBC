#include "RenderUtil.h"
#include <iostream>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/quaternion.hpp>
#include <mutex>
#include <future>
//#include "Model.h"
//#include "Shader.h"

namespace Reality
{
	RenderUtil::RenderUtil(const std::shared_ptr<Reality::AssetLoader> _assetLoader) : assetLoader(_assetLoader)
	{
		window = std::make_unique<Window>();
		window->glfwWindow = InitWindow(window->width, window->height, "RealityEngine-v1.0");
		//assetLoader = std::make_unique<AssetLoader>();
		SetupUBOs();
		SetUpPrimitiveShaders();
		SetUpCubePrimitive();
		SetUpSpherePrimitive();
		SetUpLinePrimitive();
		SetupTrianglePrimitive();
		SetupTextRender();
	}


	GLFWwindow* RenderUtil::InitWindow(int width, int height, const char* title)
	{
		// glfw: initialize and configure
			// ------------------------------
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		#endif

		// glfw window creation
		// --------------------
		GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
		if (window == NULL)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return NULL;
		}
		glfwMakeContextCurrent(window);

		// tell GLFW to capture our mouse
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		// glad: load all OpenGL function pointers
		// ---------------------------------------
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return NULL;
		}

		// configure global opengl state
		// -----------------------------
		glEnable(GL_DEPTH_TEST);
		return window;
	}

	void RenderUtil::SetupUBOs()
	{
		// Matrices
		glGenBuffers(1, &uboMatrices);

		glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
		glBufferData(GL_UNIFORM_BUFFER, 3 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);

		glBindBufferRange(GL_UNIFORM_BUFFER, 0, uboMatrices, 0, 3 * sizeof(glm::mat4));

		// Dir Lights
		glGenBuffers(1, &uboDirectionalLights);

		glBindBuffer(GL_UNIFORM_BUFFER, uboDirectionalLights);
		glBufferData(GL_UNIFORM_BUFFER, MAX_DIR_LIGHTS * sizeof(DirLight) + sizeof(int), NULL, GL_STATIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);

		glBindBufferRange(GL_UNIFORM_BUFFER, 1, uboDirectionalLights, 0, MAX_DIR_LIGHTS * sizeof(DirLight) + sizeof(int));

		// Point Lights
		glGenBuffers(1, &uboPointLights);

		glBindBuffer(GL_UNIFORM_BUFFER, uboPointLights);
		glBufferData(GL_UNIFORM_BUFFER, MAX_POINT_LIGHTS * sizeof(PointLight) + sizeof(int), NULL, GL_STATIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);

		glBindBufferRange(GL_UNIFORM_BUFFER, 2, uboPointLights, 0, MAX_POINT_LIGHTS * sizeof(PointLight) + sizeof(int));

		// Spot Lights
		glGenBuffers(1, &uboSpotLights);

		glBindBuffer(GL_UNIFORM_BUFFER, uboSpotLights);
		glBufferData(GL_UNIFORM_BUFFER, MAX_SPOT_LIGHTS * sizeof(SpotLight) + sizeof(int), NULL, GL_STATIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);

		glBindBufferRange(GL_UNIFORM_BUFFER, 3, uboSpotLights, 0, MAX_SPOT_LIGHTS * sizeof(SpotLight) + sizeof(int));
	}

	void RenderUtil::DrawModel(int modelID, const glm::vec3& position, const glm::vec3& scale, const glm::vec3& rotation, unsigned int drawMode)
	{
		float time = glfwGetTime();
		if (assetLoader->IsValid(modelID))
		{
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glPolygonMode(GL_FRONT_AND_BACK, drawMode);
			SetModelTransform(position, scale, rotation);
			Model* modelToDraw = assetLoader->GetModel(modelID);
			modelToDraw->Draw();
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			verts += modelToDraw->verts;
			triangles += modelToDraw->verts / 3;
			drawCalls += modelToDraw->meshes.size();
		}
		renderDeltaTime += glfwGetTime() - time;
	}

	void RenderUtil::DrawModel(int modelID, glm::mat4 modelMatrix, unsigned int drawMode)
	{
		float time = glfwGetTime();
		if (assetLoader->IsValid(modelID))
		{
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glPolygonMode(GL_FRONT_AND_BACK, drawMode);
			SetModelTransform(modelMatrix);
			Model* modelToDraw = assetLoader->GetModel(modelID);
			modelToDraw->Draw();
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			verts += modelToDraw->verts;
			triangles += modelToDraw->verts / 3;
			drawCalls += modelToDraw->meshes.size();
		}
		renderDeltaTime += glfwGetTime() - time;
	}

	void RenderUtil::ClearDisplay(GLFWwindow* window)
	{
		glClearColor(0.0f, 0.025f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		verts = 0;
		triangles = 0;
		lines = 0;
		drawCalls = 0;
		renderDeltaTime = 0;
	}

	void RenderUtil::SwapBuffers(GLFWwindow* window)
	{
		glfwSwapBuffers(window);
	}

	void RenderUtil::SetUpPrimitiveShaders()
	{
		primitiveShader.Init();
		primitiveShaderBasic.Init();
		textShader.Init();
	}

	void RenderUtil::SetUpCubePrimitive()
	{
		// set up vertex data (and buffer(s)) and configure vertex attributes
		// ------------------------------------------------------------------
		float vertices[] = {
			// positions          // normals           // texture coords
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
			 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
		};

		glGenVertexArrays(1, &cubeVAO);
		glGenBuffers(1, &cubeVBO);

		glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindVertexArray(cubeVAO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);
	}

	void RenderUtil::SetUpSpherePrimitive()
	{
		std::vector<float> VNT;
		float radius = 1;
		float PI = 3.14f;
		int sectorCount = 40;
		int stackCount = 16;

		float x, y, z, xy;                              // vertex position
		float nx, ny, nz, lengthInv = 1.0f / radius;    // vertex normal
		float s, t;                                     // vertex texCoord

		float sectorStep = 2 * PI / sectorCount;
		float stackStep = PI / stackCount;
		float sectorAngle, stackAngle;

		for (int i = 0; i <= stackCount; ++i)
		{
			stackAngle = PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
			xy = radius * cosf(stackAngle);             // r * cos(u)
			z = radius * sinf(stackAngle);              // r * sin(u)

			// add (sectorCount+1) vertices per stack
			// the first and last vertices have same position and normal, but different tex coords
			for (int j = 0; j <= sectorCount; ++j)
			{
				sectorAngle = j * sectorStep;           // starting from 0 to 2pi

				// vertex position (x, y, z)
				x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
				y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)
				VNT.push_back(x);
				VNT.push_back(y);
				VNT.push_back(z);

				// normalized vertex normal (nx, ny, nz)
				nx = x * lengthInv;
				ny = y * lengthInv;
				nz = z * lengthInv;
				VNT.push_back(nx);
				VNT.push_back(ny);
				VNT.push_back(nz);

				// vertex tex coord (s, t) range between [0, 1]
				s = (float)j / sectorCount;
				t = (float)i / stackCount;
				VNT.push_back(s);
				VNT.push_back(t);
			}
		}

		std::vector<int> indices;
		int k1, k2;
		for (int i = 0; i < stackCount; ++i)
		{
			k1 = i * (sectorCount + 1);     // beginning of current stack
			k2 = k1 + sectorCount + 1;      // beginning of next stack

			for (int j = 0; j < sectorCount; ++j, ++k1, ++k2)
			{
				// 2 triangles per sector excluding first and last stacks
				// k1 => k2 => k1+1
				if (i != 0)
				{
					indices.push_back(k1);
					indices.push_back(k2);
					indices.push_back(k1 + 1);
				}

				// k1+1 => k2 => k2+1
				if (i != (stackCount - 1))
				{
					indices.push_back(k1 + 1);
					indices.push_back(k2);
					indices.push_back(k2 + 1);
				}
			}
		}

		numIndices = indices.size();

		// Bind Buffers
		glGenVertexArrays(1, &sphereVAO);
		glBindVertexArray(sphereVAO);

		// copy interleaved vertex data (V/N/T) to VBO
		glGenBuffers(1, &sphereVBO);
		glBindBuffer(GL_ARRAY_BUFFER, sphereVBO);       // for vertex data
		glBufferData(GL_ARRAY_BUFFER,                   // target
			VNT.size() * sizeof(float),									// data size, # of bytes
			&VNT[0],									// ptr to vertex data
			GL_STATIC_DRAW);							// usage

		// copy index data to VBO
		glGenBuffers(1, &sphereIBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sphereIBO);   // for index data
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,				// target
			indices.size() * sizeof(int),									// data size, # of bytes
			&indices[0],									// ptr to index data
			GL_STATIC_DRAW);								// usage

		// bind VBOs
		//glBindBuffer(GL_ARRAY_BUFFER, sphereVBO);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sphereIBO);

		// activate attrib arrays
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		// set attrib arrays with stride and offset
		int stride = sizeof(float) * 8;     // should be 32 bytes
		glVertexAttribPointer(0, 3, GL_FLOAT, false, stride, (void*)0);
		glVertexAttribPointer(1, 3, GL_FLOAT, false, stride, (void*)(sizeof(float) * 3));
		glVertexAttribPointer(2, 2, GL_FLOAT, false, stride, (void*)(sizeof(float) * 6));
	}

	void RenderUtil::SetUpLinePrimitive()
	{
		// set up vertex data (and buffer(s)) and configure vertex attributes
		// ------------------------------------------------------------------
		float vertices[] = {
			// positions         
			 0.0f, 0.0f, 0.0f,
			 1.0f, 0.0f, 0.0f
		};

		glGenVertexArrays(1, &lineVAO);
		glGenBuffers(1, &lineVBO);

		glBindBuffer(GL_ARRAY_BUFFER, lineVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindVertexArray(lineVAO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
	}

	void RenderUtil::SetupTrianglePrimitive()
	{
		glGenVertexArrays(1, &triangleVAO);
		glGenBuffers(1, &triangleVBO);
	}

	void RenderUtil::SetupTextRender()
	{
		// Setup the shader
		glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(window->width), 0.0f, static_cast<GLfloat>(window->height));
		textShader.use();
		glUniformMatrix4fv(glGetUniformLocation(textShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		// FreeType
		FT_Library ft;
		// All functions return a value different than 0 whenever an error occurred
		if (FT_Init_FreeType(&ft))
			std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

		// Load font as face
		FT_Face face;
		if (FT_New_Face(ft, "Fonts/Arial.ttf", 0, &face))
			std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

		// Set size to load glyphs as
		FT_Set_Pixel_Sizes(face, 0, 48);

		// Disable byte-alignment restriction
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		// Load first 128 characters of ASCII set
		for (GLubyte c = 0; c < 128; c++)
		{
			// Load character glyph 
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			{
				std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
				continue;
			}
			// Generate texture
			GLuint texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RED,
				face->glyph->bitmap.width,
				face->glyph->bitmap.rows,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				face->glyph->bitmap.buffer
			);
			// Set texture options
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			// Now store character for later use
			Character character = {
				texture,
				glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				face->glyph->advance.x
			};
			Characters.insert(std::pair<GLchar, Character>(c, character));
		}
		glBindTexture(GL_TEXTURE_2D, 0);
		// Destroy FreeType once we're finished
		FT_Done_Face(face);
		FT_Done_FreeType(ft);


		// Configure VAO/VBO for texture quads
		glGenVertexArrays(1, &textVAO);
		glGenBuffers(1, &textVBO);
		glBindVertexArray(textVAO);
		glBindBuffer(GL_ARRAY_BUFFER, textVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void RenderUtil::RenderText(std::string text, float x, float y, float scale, Color color)
	{
		float time = glfwGetTime();
		glEnable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Activate corresponding render state	
		textShader.use();
		glUniform3f(glGetUniformLocation(textShader.ID, "textColor"), color.r, color.g, color.b);
		glActiveTexture(GL_TEXTURE0);
		glBindVertexArray(textVAO);

		// Iterate through all characters
		std::string::const_iterator c;
		for (c = text.begin(); c != text.end(); c++)
		{
			Character ch = Characters[*c];

			GLfloat xpos = x + ch.Bearing.x * scale;
			GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

			GLfloat w = ch.Size.x * scale;
			GLfloat h = ch.Size.y * scale;
			// Update VBO for each character
			GLfloat vertices[6][4] = {
				{ xpos,     ypos + h,   0.0, 0.0 },
				{ xpos,     ypos,       0.0, 1.0 },
				{ xpos + w, ypos,       1.0, 1.0 },

				{ xpos,     ypos + h,   0.0, 0.0 },
				{ xpos + w, ypos,       1.0, 1.0 },
				{ xpos + w, ypos + h,   1.0, 0.0 }
			};
			// Render glyph texture over quad
			glBindTexture(GL_TEXTURE_2D, ch.TextureID);
			// Update content of VBO memory
			glBindBuffer(GL_ARRAY_BUFFER, textVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			// Render quad
			glDrawArrays(GL_TRIANGLES, 0, 6);
			verts += 6;
			triangles += 2;
			drawCalls++;
			// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
			x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
		}
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);

		glDisable(GL_CULL_FACE);
		glDisable(GL_BLEND);
		renderDeltaTime += glfwGetTime() - time;
	}

	void RenderUtil::DrawCube(const glm::vec3& position, const glm::vec3& scale, const glm::vec3& rotation, const Color& color)
	{
		float time = glfwGetTime();
		glBindVertexArray(cubeVAO);
		primitiveShader.use();

		SetModelTransform(position, scale, rotation);

		primitiveShader.setVec3("col", glm::vec3(color.r, color.g, color.b));

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		verts += 36;
		triangles += 12;
		drawCalls++;
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		renderDeltaTime += glfwGetTime() - time;
	}

	void RenderUtil::DrawCube(const glm::vec3 & position, const glm::vec3 & scale, const glm::quat& orientation, const Color & color)
	{
		float time = glfwGetTime();
		glBindVertexArray(cubeVAO);
		primitiveShader.use();

		SetModelTransform(position, scale, orientation);

		primitiveShader.setVec3("col", glm::vec3(color.r, color.g, color.b));

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		verts += 36;
		triangles += 12;
		drawCalls++;
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		renderDeltaTime += glfwGetTime() - time;
	}

	void RenderUtil::DrawSphere(const glm::vec3& position, float radius, const Color& color)
	{
		glBindVertexArray(sphereVAO);
		primitiveShader.use();

		SetModelTransform(position, glm::vec3(radius, radius, radius), glm::vec3(0,0,0));

		primitiveShader.setVec3("col", glm::vec3(color.r, color.g, color.b));
		// draw a sphere with VBO
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawElements(GL_TRIANGLES,        // primitive type
			numIndices,						// # of indices
			GL_UNSIGNED_INT,                // data type
			(void*)0);                      // offset to indices
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	void RenderUtil::DrawLine(const glm::vec3& start, const glm::vec3& end, const Color& color)
	{
		float time = glfwGetTime();
		glBindVertexArray(lineVAO);
		primitiveShaderBasic.use();

		glm::vec3 position = (start + end) * 0.5f;
		float scale = glm::length(start - end);
		glm::vec3 axis = glm::cross(glm::vec3(1, 0, 0), end - start);
		axis = glm::normalize(axis);
		float proj = glm::dot(end - start, glm::vec3(1, 0, 0));
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, start);
		model = glm::rotate(model, glm::orientedAngle(glm::vec3(1, 0, 0), glm::normalize(end - start), axis), axis);
		model = glm::scale(model, glm::vec3(scale, scale, scale));
		SetModelTransform(model);

		primitiveShaderBasic.setVec3("col", glm::vec3(color.r, color.g, color.b));

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawArrays(GL_LINES, 0, 2);
		verts += 2;
		lines += 1;
		drawCalls++;
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		renderDeltaTime += glfwGetTime() - time;
	}

	void RenderUtil::DrawTriangle(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c, const Color& color)
	{
		float time = glfwGetTime();

		glm::vec3 vertices[] = {a,b,c};

		glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindVertexArray(triangleVAO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		primitiveShader.use();

		SetModelTransform(glm::mat4(1.0f));

		primitiveShader.setVec3("col", glm::vec3(color.r, color.g, color.b));

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		verts += 3;
		triangles += 1;
		drawCalls++;
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		renderDeltaTime += glfwGetTime() - time;
	}

	void RenderUtil::SetFOV(float fov)
	{
		glm::mat4 projection = glm::perspective(glm::radians(fov), (float)window->width / (float)window->height, 0.1f, 100000.0f);
		glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	void RenderUtil::UpdateViewMatrix()
	{
		glm::mat4 view = camera.GetViewMatrix();
		glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
		glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	void RenderUtil::SetModelTransform(const glm::mat4 model)
	{
		glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
		glBufferSubData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(model));
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	void RenderUtil::SetModelTransform(const glm::vec3& position, const glm::vec3& scale, const glm::vec3& rotation)
	{
		glm::vec3 rotationInRads = glm::vec3(glm::radians(rotation.x), glm::radians(rotation.y), glm::radians(rotation.z));
		glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), scale);
		glm::mat4 translateMat = glm::translate(glm::mat4(1.0f), position);
		glm::mat4 rotationMat =  glm::toMat4(glm::quat(rotationInRads));
		SetModelTransform(translateMat * rotationMat * scaleMat);
	}

	void RenderUtil::SetModelTransform(const glm::vec3& position, const glm::vec3& scale, const glm::quat& orientation)
	{
		glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), scale);
		glm::mat4 translateMat = glm::translate(glm::mat4(1.0f), position);
		glm::mat4 rotationMat = glm::toMat4(orientation);
		SetModelTransform(translateMat * rotationMat * scaleMat);
	}

	void RenderUtil::UpdateDirLights(const std::vector<DirLight>& lightArray, int numLights)
	{
		glBindBuffer(GL_UNIFORM_BUFFER, uboDirectionalLights);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, numLights * sizeof(DirLight), &lightArray[0]);
		glBufferSubData(GL_UNIFORM_BUFFER, MAX_DIR_LIGHTS * sizeof(DirLight), sizeof(int), &numLights);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	void RenderUtil::UpdatePointLights(const std::vector<PointLight>& lightArray, int numLights)
	{
		glBindBuffer(GL_UNIFORM_BUFFER, uboPointLights);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, numLights * sizeof(PointLight), &lightArray[0]);
		glBufferSubData(GL_UNIFORM_BUFFER, MAX_POINT_LIGHTS * sizeof(PointLight), sizeof(int), &numLights);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	void RenderUtil::UpdateSpotLights(const std::vector<SpotLight>& lightArray, int numLights)
	{
		glBindBuffer(GL_UNIFORM_BUFFER, uboSpotLights);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, numLights * sizeof(SpotLight), &lightArray[0]);
		glBufferSubData(GL_UNIFORM_BUFFER, MAX_SPOT_LIGHTS * sizeof(SpotLight), sizeof(int), &numLights);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}
}
