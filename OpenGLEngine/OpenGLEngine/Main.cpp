//#define STB_IMAGE_IMPLEMENTATION
// Submission for Team Cube
// Team Members : Nathan Whitehead 101242269, Jesse Rubin 101231958, Phoenix Makins 101193192
#include "RenderingSystem.h"
#include "InputEventSystem.h"
#include "FPSControlSystem.h"
#include "RotateSystem.h"
#include "FireworksSystem.h"
#include "GravityForceSystem.h"
#include "ForceAccumulatorSystem.h"
#include "DragForceSystem.h"
#include "FixedSpringSystem.h"
#include "PairedSpringSystem.h"
#include "ParticleSystem.h"
#include "DynamicDirectionalLightSystem.h"
#include "DynamicPointLightSystem.h"
#include "DynamicSpotLightSystem.h"
#include "BuoyancyForceSystem.h"
#include "NBodySystem.h"
#include <string>
#include <stdlib.h>     
#include <time.h>    
//#include <vector>

using namespace Reality;

void LoadShaders(ECSWorld& world);
void LoadModels(ECSWorld& world);
void SetupLights(ECSWorld& world);
void MakeABunchaObjects(ECSWorld& world);
void MakeFireworks(ECSWorld& world);
// Needed for Assignment 1
int testInput = 0; // this will handle what part we are testing and only enable input for said test
void OurInput(ECSWorld& world); // our input handling for all of the tests
// Part 1
void StartParticle(ECSWorld& world);
void BungeeCord(ECSWorld& world);
bool pressed = false;
ECSEntity lastNode;
// Part 2
void BuoyancyTest(ECSWorld& world);
void AddBuoyantObject(ECSWorld& world);
//Part 3
void NBodyTest(ECSWorld& world);
int main()
{
	ECSWorld world;

	// Init and Load
	world.data.InitRendering();
	//LoadAssets(world);
	
	world.data.renderUtil->camera.Position = Vector3(0, 40.0f, 50.0f);
	world.data.renderUtil->SetFOV(60);
	// Create entities

	// Make a player controller
	auto e = world.createEntity();
	e.addComponent<FPSControlComponent>();

	SetupLights(world);
	
	

	// Create Systems
	world.getSystemManager().addSystem<RenderingSystem>();
	world.getSystemManager().addSystem<InputEventSystem>();
	world.getSystemManager().addSystem<FPSControlSystem>();
	world.getSystemManager().addSystem<RotateSystem>();
	world.getSystemManager().addSystem<FireworksSystem>();
	world.getSystemManager().addSystem<GravityForceSystem>();
	world.getSystemManager().addSystem<ForceAccumulatorSystem>();
	world.getSystemManager().addSystem<ParticleSystem>();
	world.getSystemManager().addSystem<DynamicDirectionalLightSystem>();
	world.getSystemManager().addSystem<DynamicPointLightSystem>();
	world.getSystemManager().addSystem<DynamicSpotLightSystem>();
	world.getSystemManager().addSystem<DragForceSystem>();
	world.getSystemManager().addSystem<PairedSpringSystem>();
	// Systems used for assignment 1
	world.getSystemManager().addSystem<FixedSpringSystem>();
	world.getSystemManager().addSystem<BuoyancyForceSystem>();
	world.getSystemManager().addSystem<NBodySystem>();

	float time = glfwGetTime();
	float stepTime = glfwGetTime();
	float deltaTime = 0;
	float elapsedDeltaTime = 0;
	float logicDelta = 0;
	float debugDelta = 0;



	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// To test the first part please uncomment StartParticle(world);                         ///////    ///////    ////     /////    /////////////////////////////////////////////////////////////
	// To test the second part please uncomment BuoyancyTest(world);                         ///////    ///////    ////     /////    /////////////////////////////////////////////////////////////
	// To test the third part please uncomment NBodyTest(world);                             ///////    ///////    ////     /////    /////////////////////////////////////////////////////////////
	// The starting particle for part 1                                                      ///////               ////     /////    /////////////////////////////////////////////////////////////
	StartParticle(world);                                                                  ///////               ////     /////    /////////////////////////////////////////////////////////////
	// The start for buoyancy par 2                                                          ///////    ///////    ////     /////    /////////////////////////////////////////////////////////////
	//BuoyancyTest(world);                                                                   ///////    ///////    ////     //////////////////////////////////////////////////////////////////////
	// The start for Nbodies part 3                                                          ///////    ///////    ////     /////    /////////////////////////////////////////////////////////////
	//NBodyTest(world);                                                                      ///////    ///////    ////     /////    /////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	LoadShaders(world);
	bool shadersLoaded = false;
	bool modelsLoadStarted = false;
	// game loop
	// -----------
	while (!glfwWindowShouldClose(world.data.renderUtil->window->glfwWindow))
	{
		float current = glfwGetTime();
		deltaTime = current - time;
		deltaTime = 1 / 60.0f;
		time = glfwGetTime();

		world.update();

		// Poll OpenGl events
		glfwPollEvents();

		world.data.renderUtil->ClearDisplay(world.data.renderUtil->window->glfwWindow);

		// Load
		if (!shadersLoaded)
		{
			shadersLoaded = world.data.assetLoader->ShadersLoaded();
		}
		if(shadersLoaded && !modelsLoadStarted)
		{
			LoadModels(world);
			modelsLoadStarted = true;
		}
		// Update View
		world.data.renderUtil->UpdateViewMatrix();
		// Process Input
		world.getSystemManager().getSystem<InputEventSystem>().Update(deltaTime);
		OurInput(world);

		// Game Logic Update
		world.getSystemManager().getSystem<FPSControlSystem>().Update(deltaTime);
		world.getSystemManager().getSystem<RotateSystem>().Update(deltaTime);
		world.getSystemManager().getSystem<FireworksSystem>().Update(deltaTime);

		// Update Transform

		// Physics
		//float fixedDeltaTime = glfwGetKey(world.data.renderUtil->window->glfwWindow, GLFW_KEY_SPACE) == GLFW_PRESS ? 1 / 60.0f : 0;		
		float fixedDeltaTime = 1 / 60.0f;
		// Force Generator
		if (testInput != 0)
		{
			world.getSystemManager().getSystem<GravityForceSystem>().Update(fixedDeltaTime);
		}
		world.getSystemManager().getSystem<DragForceSystem>().Update(fixedDeltaTime);
		world.getSystemManager().getSystem<FixedSpringSystem>().Update(fixedDeltaTime);
		world.getSystemManager().getSystem<PairedSpringSystem>().Update(fixedDeltaTime);
		if (testInput == 2)
		{
			world.getSystemManager().getSystem<BuoyancyForceSystem>().Update(fixedDeltaTime);
		}
		world.getSystemManager().getSystem<NBodySystem>().Update(fixedDeltaTime);

		// Force Accumulator
		world.getSystemManager().getSystem<ForceAccumulatorSystem>().Update(fixedDeltaTime);

		// Integrator
		world.getSystemManager().getSystem<ParticleSystem>().Update(fixedDeltaTime);

		// Rendering Update
		world.getSystemManager().getSystem<DynamicDirectionalLightSystem>().Update(deltaTime);
		world.getSystemManager().getSystem<DynamicPointLightSystem>().Update(deltaTime);
		world.getSystemManager().getSystem<DynamicSpotLightSystem>().Update(deltaTime);
		world.getSystemManager().getSystem<RenderingSystem>().Update(deltaTime);

		elapsedDeltaTime = glfwGetTime() - time;
		logicDelta = elapsedDeltaTime - world.data.renderUtil->GetRenderDelta();
		stepTime = glfwGetTime();

		// Debug
		if (DEBUG_LOG_LEVEL > 0)
		{
			world.data.renderUtil->RenderText("FPS : " + std::to_string((int)round(1.0f / deltaTime)), 1810.0f, 1060.0f, 0.5f, Color(0, 1, 1, 1));
		}
		if (DEBUG_LOG_LEVEL > 1)
		{
			int logic = (int)round(logicDelta * 100.0f / deltaTime);
			std::string logicString = logic < 10 ? " " + std::to_string(logic) : std::to_string(logic);
			int render = (int)round(world.data.renderUtil->GetRenderDelta() * 100.0f / deltaTime);
			std::string renderString = logic < 10 ? " " + std::to_string(render) : std::to_string(render);
			int debug = (int)round(debugDelta * 100.0f / deltaTime);
			std::string debugString = logic < 10 ? " " + std::to_string(debug) : std::to_string(debug);
			
			world.data.renderUtil->RenderText("Logic : " + logicString + "%" +
				//+ " | Physics : " + std::to_string((int)round(physicsDelta * 100.0f / deltaTime)) + "%" +
				+ " | Rendering : " + renderString + "%" +
				+ " | Debug : " + debugString + "%"
				, 1680.0f, 1040.0f, 0.25f, Color(0, 1, 1, 1));
		}
		if (DEBUG_LOG_LEVEL > 2)
		{
			world.data.renderUtil->RenderText("Draw Calls : " + std::to_string(world.data.renderUtil->GetDrawCalls())
				+ " | Verts : " + std::to_string(world.data.renderUtil->GetVerts())
				+ " | Tris : " + std::to_string(world.data.renderUtil->GetTris())
				+ " | Lines : " + std::to_string(world.data.renderUtil->GetLines())
				, 1610.0f, 1020.0f, 0.25f, Color(0, 1, 1, 1));
		}

		// Update debug delta
		debugDelta = glfwGetTime() - stepTime;
		stepTime = glfwGetTime();

		world.data.renderUtil->SwapBuffers(world.data.renderUtil->window->glfwWindow);

		// Show FPS in console
		//std::cout << "FPS : " << 1.0f / deltaTime << std::endl;
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

void LoadShaders(ECSWorld& world)
{
	world.data.assetLoader->StartShaderLoading({ {"Shaders/Lighting_Maps.vs", "Shaders/Lighting_Maps.fs"} });
}
void LoadModels(ECSWorld& world)
{
	world.data.assetLoader->StartModelLoading({
		//ModelData("Resources/Models/snowy-mountain-terrain/SnowyMountainMesh.obj"),
		ModelData("Resources/Models/Sponza-master/sponza.obj"),
		ModelData("Resources/Models/nanosuit/nanosuit.obj"),
		ModelData("Resources/Models/supermarine-spitfire/spitfire.fbx",
			{{"spitfire_d.png"}})
		});
}

void MakeABunchaObjects(ECSWorld& world)
{
	auto castle = world.createEntity();
	castle.addComponent<TransformComponent>(Vector3(0, -3.0f, 0.0f), Vector3(0.1f, 0.1f, 0.1f), Vector3(0, 270, 0));
	// Add mesh
	castle.addComponent<ModelComponent>("Resources/Models/Sponza-master/sponza.obj");

	//auto flight = world.createEntity();
	//flight.addComponent<TransformComponent>(Vector3(0, 30, -50), Vector3(0.1f, 0.1f, 0.1f), Vector3(270, 0, 0));
	//// Add mesh
	//flight.addComponent<ModelComponent>("Resources/Models/supermarine-spitfire/spitfire.fbx");
	//flight.addComponent<RotateComponent>(Vector3(0, 90, 0));
	//flight.addComponent<ParticleComponent>(Vector3(0, 30, 0));
	//flight.addComponent<ForceAccumulatorComponent>();
	//flight.addComponent<GravityForceComponent>();

}

void MakeFireworks(ECSWorld & world)
{
	for (int i = 0; i < 3; i++)
	{
		auto fireworks = world.createEntity();
		fireworks.addComponent<TransformComponent>(Vector3(-100 + 100 * i, 30 + RANDOM_FLOAT(-10, 10), -50));
		fireworks.addComponent<ParticleComponent>(Vector3(0, 100, 0));
		fireworks.addComponent<ForceAccumulatorComponent>();
		fireworks.addComponent<GravityForceComponent>();
		fireworks.addComponent<FireworksComponent>(6, 3, 3 + RANDOM_FLOAT(-1, 1));
	}
	
}
// The initial test for Bungee cord
void StartParticle(ECSWorld& world)
{
	testInput = 1;
	auto partWithDrag = world.createEntity();
	partWithDrag.addComponent<TransformComponent>(Vector3(0, 30, -50));
	partWithDrag.addComponent<ParticleComponent>(Vector3(0, 50, 0));
	partWithDrag.addComponent<ForceAccumulatorComponent>();
	partWithDrag.addComponent<GravityForceComponent>();

	
	/*//partWithDrag.addComponent<DragForceComponent>(1.0f, 0.0f);
	//partWithDrag.addComponent<FixedSpringComponent>(1.0f, 100.0f, partWithDrag);

	//auto partWithDrag2 = world.createEntity();
	//partWithDrag2.addComponent<TransformComponent>(Vector3(100, 30, -50));
	//partWithDrag2.addComponent<ParticleComponent>(Vector3(0, 50, 0));
	//partWithDrag2.addComponent<ForceAccumulatorComponent>();
	//partWithDrag2.addComponent<GravityForceComponent>();
	//partWithDrag2.addComponent<DragForceComponent>(1.0f, 0.0f);
	////partWithDrag.addComponent<FixedSpringComponent>(1.0f, 100.0f, partWithDrag2);

	//auto partWithDrag3 = world.createEntity();
	//partWithDrag3.addComponent<TransformComponent>(Vector3(200, 30, -50));
	//partWithDrag3.addComponent<ParticleComponent>(Vector3(0, 50, 0));
	//partWithDrag3.addComponent<ForceAccumulatorComponent>();
	//partWithDrag3.addComponent<GravityForceComponent>();
	//partWithDrag3.addComponent<DragForceComponent>(1.0f, 0.0f);
	*/
	auto spring1 = world.createEntity();
	spring1.addComponent<TransformComponent>(Vector3(0, 40, -50));
	spring1.addComponent<FixedSpringComponent>(10, 50, partWithDrag);

	lastNode = partWithDrag;

}
// Adding a new particle with spring to last particle created
void BungeeCord(ECSWorld& world)
{
	Vector3 cameraPosition = world.data.renderUtil->camera.Position;

	auto nextJump = world.createEntity();
	nextJump.addComponent<TransformComponent>(cameraPosition);
	nextJump.addComponent<ParticleComponent>(Vector3(0, 50, 0));
	nextJump.addComponent<ForceAccumulatorComponent>();
	nextJump.addComponent<GravityForceComponent>();

	auto spring1 = world.createEntity();
	spring1.addComponent<TransformComponent>(Vector3(0, 40, -50));
	spring1.addComponent<PairedSpringComponent>(2, 20, lastNode, nextJump);

	lastNode = nextJump;
}
// The initial test for Buoyancy
void BuoyancyTest(ECSWorld& world)
{
	testInput = 2;
	//auto water = world.createEntity();
	//water.addComponent<BuoyancyComponent>(1.0f, 1.0f);
	
	auto pointInWater = world.createEntity();
	pointInWater.addComponent<TransformComponent>(Vector3(0, 4, 0), Vector3(1,1,1), Vector3(0,0,0));
	pointInWater.addComponent<ForceAccumulatorComponent>();
	pointInWater.addComponent<ParticleComponent>(Vector3(0, 30, 0));
	pointInWater.addComponent<GravityForceComponent>();
	pointInWater.addComponent<BuoyancyComponent>(1.0f, 1.0f);
}
// Adding a new particle to scene
void AddBuoyantObject(ECSWorld& world)
{
	Vector3 cameraPosition = world.data.renderUtil->camera.Position + 100.0f * world.data.renderUtil->camera.Front;


	auto newObject = world.createEntity();
	newObject.addComponent<TransformComponent>(cameraPosition);
	newObject.addComponent<ForceAccumulatorComponent>();
	newObject.addComponent<ParticleComponent>(Vector3(0, 30, 0));
	newObject.addComponent<GravityForceComponent>();
	newObject.addComponent<BuoyancyComponent>(1.0f, 1.0f);
}
// NBody test function
void NBodyTest(ECSWorld& world)
{
	testInput = 0;
	Vector3 cameraPosition = world.data.renderUtil->camera.Position;

	for (int i = 0; i < 10; i++)
	{
		auto nBody = world.createEntity();
		nBody.addComponent<ParticleComponent>(Vector3(0,0,0));
		nBody.addComponent<TransformComponent>(cameraPosition + Vector3(RANDOM_FLOAT(0, 600),RANDOM_FLOAT(0, 600),RANDOM_FLOAT(0, 600)), Vector3(1,1,1), Vector3(0,0,0));
		nBody.addComponent<NBodyComponent>(50);
		nBody.addComponent<ForceAccumulatorComponent>();
	}
	/* The pun
	auto nBody = world.createEntity();
		nBody.addComponent<ParticleComponent>(Vector3(0,0,0));
		nBody.addComponent<TransformComponent>(cameraPosition, Vector3(1,1,1), Vector3(0,0,0));
		nBody.addComponent<NBodyComponent>(5000);
		nBody.addComponent<ForceAccumulatorComponent>();
	*/
}

void OurInput(ECSWorld& world)
{
	GLFWwindow* window = world.data.renderUtil->window->glfwWindow;
	
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		pressed = true;
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE && pressed)
	{
		if (testInput == 1)
		{
			BungeeCord(world);
		}
		if (testInput == 2)
		{
			AddBuoyantObject(world);
		}
		pressed = false;
	}
	// Left and right arrow for density
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		if (testInput == 2)
		{
			BuoyancyForceSystem::liquidDensity += 10;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		if (testInput == 2 && BuoyancyForceSystem::liquidDensity > 40)
		{
			BuoyancyForceSystem::liquidDensity -= 10;
		}
	}
}

void SetupLights(ECSWorld& world)
{
	auto l = world.createEntity();
	l.addComponent<TransformComponent>(Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(90, 0, 0));
	l.addComponent<DynamicDirectionalLightComponent>(Color(0.0, 0.1, 0.1), Color(0.0, 0.1, 0.1), Color(0.0, 0.1, 0.1));

	// Lanterns
	auto pl1 = world.createEntity();
	pl1.addComponent<TransformComponent>(Vector3(22, 14, 48.5f));
	pl1.addComponent<DynamicPointLightComponent>(100.0f, Color(0.1, 0, 0), Color(1.0f, 0.0f, 0.0f), Color(1.0f, 0.0f, 0.0f));
	auto hook = world.createEntity();
	hook.addComponent<TransformComponent>(Vector3(23, 15, 48.0f));
	hook = world.createEntity();
	hook.addComponent<TransformComponent>(Vector3(22, 13.5f, 50.5f));
	hook = world.createEntity();
	hook.addComponent<TransformComponent>(Vector3(21, 12.5f, 47.5f));

	auto pl2 = world.createEntity();
	pl2.addComponent<TransformComponent>(Vector3(-14.5f, 14, 49.0f));
	pl2.addComponent<DynamicPointLightComponent>(100.0f, Color(0, 0, 0.1f), Color(0.0f, 0.0f, 1.0f), Color(0.0f, 0.0f, 1.0f));
	hook = world.createEntity();
	hook.addComponent<TransformComponent>(Vector3(-14.5f + 1, 14 - 1, 49.0f - 1));
	hook = world.createEntity();
	hook.addComponent<TransformComponent>(Vector3(-14.5f - 0.5f, 14 + 1, 49.0f));
	hook = world.createEntity();
	hook.addComponent<TransformComponent>(Vector3(-14.5f, 14 - 1, 49.0f + 1));
	
	auto pl3 = world.createEntity();
	pl3.addComponent<TransformComponent>(Vector3(22, 14, -62.0f));
	pl3.addComponent<DynamicPointLightComponent>(100.0f, Color(0, 0.1f, 0), Color(0.0f, 1.0f, 0.0f), Color(0.0f, 1.0f, 0.0f));
	hook = world.createEntity();
	hook.addComponent<TransformComponent>(Vector3(22 - 1, 14 - 1, -62.0f));
	hook = world.createEntity();
	hook.addComponent<TransformComponent>(Vector3(22, 14 + 0.5f, -62.0f - 1));
	hook = world.createEntity();
	hook.addComponent<TransformComponent>(Vector3(22 + 1, 14, -62.0f + 0.5f));

	auto pl4 = world.createEntity();
	pl4.addComponent<TransformComponent>(Vector3(-14.5f, 14, -61.5f));
	pl4.addComponent<DynamicPointLightComponent>(100.0f, Color(0.1, 0.05, 0), Color(1.0f, 0.55f, 0.0f), Color(1.0f, 0.55f, 0.0f));
	hook = world.createEntity();
	hook.addComponent<TransformComponent>(Vector3(-14.5f - 1, 14, -61.5f -1));
	hook = world.createEntity();
	hook.addComponent<TransformComponent>(Vector3(-14.5f - 0.25f, 14 - 0.5f, -61.5f + 1));
	hook = world.createEntity();
	hook.addComponent<TransformComponent>(Vector3(-14.5f + 0.5f, 14+ 1, -61.5f + 1));

	// Spears
	std::vector<Color> cols = { Color(1,0,0), Color(0,1,0), Color(0,0,1), Color(0.7f,0.55f,0) };
	for (int i = 1; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			pl1 = world.createEntity();
			pl1.addComponent<TransformComponent>(Vector3((i % 2 == 0 ? 8 : -1), 85, 49.5f - 37 * j), Vector3(1, 1, 1), Vector3(180, 0, 0));
			pl1.addComponent<DynamicSpotLightComponent>(10.0f, 100, Color(0, 0, 0), cols[3 - j], cols[3 - j], 5);
		}
	}
}