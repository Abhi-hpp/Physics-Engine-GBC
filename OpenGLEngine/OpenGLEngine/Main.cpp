//#define STB_IMAGE_IMPLEMENTATION
#include "RenderingSystem.h"
#include "InputEventSystem.h"
#include "FPSControlSystem.h"
#include "RotateSystem.h"
#include "ParticleSystem.h"
#include "ForceAccumulatorSystem.h"
#include "GravityForceSystem.h"
#include "FireworksSystem.h"
#include "DragForceSystem.h"
#include "FixedSpringSystem.h"
#include "PairedSpringSystem.h"
#include "ParticleSphereSystem.h"
#include "ParticleContactResolutionSystem.h"
#include "BungeeChordSystem.h"
#include "BungeeEndSystem.h"
#include "SpacebarResolutionSystem.h"
#include "BuoyancySystem.h"
#include "BuoyancyControlSystem.h"
#include "BuoyancyResolutionSystem.h"
#include "NBodySystem.h"
#include "DynamicDirectionalLightSystem.h"
#include "DynamicPointLightSystem.h"
#include "DynamicSpotLightSystem.h"
#include <string>
#include <stdlib.h>
#include <time.h>

using namespace Reality;

/*
	Written By: Russell Brabers, 101192571
				Nabil Babu, 101214336

	Note: Both the Bungee System and the Buoyancy System use Space Bar for events
		  Disable the necessary line under 'Assignment 1 System Updates' to prevent
		  both firing
*/

void LoadShaders(ECSWorld& world);
void LoadModels(ECSWorld& world);
void SetupLights(ECSWorld& world);
// Simulations
void MakeABunchaObjects(ECSWorld& world);
void MakeFireworks(ECSWorld& world);
void MakeThreeParticles(ECSWorld& world);
void MakeSprings(ECSWorld& world);
void SphereSystem(ECSWorld& world);
/***** Assignment 1 Simulations *****/
void Assignment1Part1(ECSWorld& world);
void Assignment1Part2(ECSWorld& world);
void Assignment1Part3(ECSWorld& world);

int main()
{
	ECSWorld world;

	// Init and Load
	world.data.InitRendering();
	//LoadAssets(world);

	world.data.renderUtil->camera.Position = Vector3(0, 15.0f, 100.0f);
	world.data.renderUtil->SetFOV(60);
	// Create entities

	// Make a player controller
	auto e = world.createEntity();
	e.addComponent<FPSControlComponent>();

	SetupLights(world);
	//MakeABunchaObjects(world);
	//MakeFireworks(world);
	//MakeThreeParticles(world);
	//MakeSprings(world);
	//SphereSystem(world);

	/***** Assignment 1 Method Calls *****/
	//Assignment1Part1(world);
	//Assignment1Part2(world);
	Assignment1Part3(world);

	// Create Systems
	world.getSystemManager().addSystem<RenderingSystem>();
	world.getSystemManager().addSystem<InputEventSystem>();
	world.getSystemManager().addSystem<FPSControlSystem>();
	world.getSystemManager().addSystem<RotateSystem>();
	world.getSystemManager().addSystem<ParticleSystem>();
	world.getSystemManager().addSystem<ForceAccumulatorSystem>();
	world.getSystemManager().addSystem<GravityForceSystem>();
	world.getSystemManager().addSystem<FireworksSystem>();
	world.getSystemManager().addSystem<DragForceSystem>();
	world.getSystemManager().addSystem<FixedSpringSystem>();
	world.getSystemManager().addSystem<PairedSpringSystem>();
	world.getSystemManager().addSystem<ParticleSphereSystem>();
	world.getSystemManager().addSystem<ParticleContactResolutionSystem>();
	/***** Assignment 1 Systems *****/
	world.getSystemManager().addSystem<BungeeChordSystem>();
	world.getSystemManager().addSystem<BungeeEndSystem>();
	world.getSystemManager().addSystem<SpacebarResolutionSystem>();
	world.getSystemManager().addSystem<BuoyancySystem>();
	world.getSystemManager().addSystem<BuoyancyControlSystem>();
	world.getSystemManager().addSystem<BuoyancyResolutionSystem>();
	world.getSystemManager().addSystem<NBodySystem>();
	/********************************/
	world.getSystemManager().addSystem<DynamicDirectionalLightSystem>();
	world.getSystemManager().addSystem<DynamicPointLightSystem>();
	world.getSystemManager().addSystem<DynamicSpotLightSystem>();

	float time = glfwGetTime();
	float stepTime = glfwGetTime();
	float deltaTime = 0;
	float elapsedDeltaTime = 0;
	float logicDelta = 0;
	float debugDelta = 0;

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
		if (shadersLoaded && !modelsLoadStarted)
		{
			LoadModels(world);
			modelsLoadStarted = true;
		}
		// Update View
		world.data.renderUtil->UpdateViewMatrix();
		// Process Input
		world.getSystemManager().getSystem<InputEventSystem>().Update(deltaTime);

		// Game Logic Update
		world.getSystemManager().getSystem<FPSControlSystem>().Update(deltaTime);
		world.getSystemManager().getSystem<RotateSystem>().Update(deltaTime);
		world.getSystemManager().getSystem<FireworksSystem>().Update(deltaTime);
		//world.getSystemManager().getSystem<ParticleSphereSystem>().Update(deltaTime);
		/***** Assignment 1 System Updates *****/
		world.getSystemManager().getSystem<BungeeEndSystem>().Update(deltaTime);
		world.getSystemManager().getSystem<BuoyancyControlSystem>().Update(deltaTime);

		// Update Transform

		// Physics
		//float fixedDeltaTime = glfwGetKey(world.data.renderUtil->window->glfwWindow, GLFW_KEY_SPACE) == GLFW_PRESS ? 1 / 60.0f : 0;		
		float fixedDeltaTime = 1 / 60.0f;

		// Force Generators
		world.getSystemManager().getSystem<GravityForceSystem>().Update(fixedDeltaTime);
		world.getSystemManager().getSystem<DragForceSystem>().Update(fixedDeltaTime);
		world.getSystemManager().getSystem<FixedSpringSystem>().Update(fixedDeltaTime);
		world.getSystemManager().getSystem<PairedSpringSystem>().Update(fixedDeltaTime);
		world.getSystemManager().getSystem<BungeeChordSystem>().Update(fixedDeltaTime);
		world.getSystemManager().getSystem<BuoyancySystem>().Update(fixedDeltaTime);
		world.getSystemManager().getSystem<NBodySystem>().Update(fixedDeltaTime);

		// Force Accumulation
		world.getSystemManager().getSystem<ForceAccumulatorSystem>().Update(fixedDeltaTime);

		// Contact Resolution
		world.getSystemManager().getSystem<ParticleContactResolutionSystem>().Update(fixedDeltaTime);

		/***** Assignment 1 Resolution Systems ****/
		world.getSystemManager().getSystem<SpacebarResolutionSystem>().Update(fixedDeltaTime);
		world.getSystemManager().getSystem<BuoyancyResolutionSystem>().Update(fixedDeltaTime);

		// Integration
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
				+" | Rendering : " + renderString + "%" +
				+" | Debug : " + debugString + "%"
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
	//auto castle = world.createEntity();
	//castle.addComponent<TransformComponent>(Vector3(0, -3.0f, 0.0f), Vector3(0.1f, 0.1f, 0.1f), Vector3(0, 270, 0));
	//// Add mesh
	//castle.addComponent<ModelComponent>("Resources/Models/Sponza-master/sponza.obj");
	// Add rotation
	//castle.addComponent<RotateComponent>(Vector3(0, 15, 0));

	auto flight = world.createEntity();
	flight.addComponent<TransformComponent>(Vector3(0, 25, -50), Vector3(0.1f, 0.1f, 0.1f), Vector3(-90, 180, 0));
	flight.addComponent<ModelComponent>("Resources/Models/supermarine-spitfire/spitfire.fbx");
	flight.addComponent<RotateComponent>(Vector3(0, 30, 0));
	flight.addComponent<ParticleComponent>(Vector3(0, 30, 0));
	flight.addComponent<GravityForceComponent>();
	flight.addComponent<ForceAccumulatorComponent>();
}

void MakeFireworks(ECSWorld& world)
{
	auto fireworks = world.createEntity();
	fireworks.addComponent<TransformComponent>(Vector3(0, 60, -50));
	fireworks.addComponent<ParticleComponent>(Vector3(0, 100, 0));
	fireworks.addComponent<ForceAccumulatorComponent>();
	fireworks.addComponent<GravityForceComponent>(0.1f);
	fireworks.addComponent<FireworksComponent>();
}

void MakeThreeParticles(ECSWorld& world)
{
	auto particle1 = world.createEntity();
	particle1.addComponent<TransformComponent>(Vector3(-20, 10, -50));
	particle1.addComponent<ParticleComponent>(Vector3(0, 0, 0));
	particle1.addComponent<ForceAccumulatorComponent>();
	particle1.addComponent<GravityForceComponent>(0.1f);
	particle1.addComponent<DragForceComponent>();

	auto particle2 = world.createEntity();
	particle2.addComponent<TransformComponent>(Vector3(0, 10, -50));
	particle2.addComponent<ParticleComponent>(Vector3(0, 0, 0));
	particle2.addComponent<ForceAccumulatorComponent>();
	particle2.addComponent<GravityForceComponent>(0.1f);
	particle2.addComponent<DragForceComponent>(1.0f, 0.0f);

	auto particle3 = world.createEntity();
	particle3.addComponent<TransformComponent>(Vector3(20, 10, -50));
	particle3.addComponent<ParticleComponent>(Vector3(0, 0, 0));
	particle3.addComponent<ForceAccumulatorComponent>();
	particle3.addComponent<GravityForceComponent>(0.1f);
	particle3.addComponent<DragForceComponent>(1.0f, 1.0f);
}

void MakeSprings(ECSWorld& world)
{
	auto particle1 = world.createEntity();
	particle1.addComponent<TransformComponent>(Vector3(0, 40, -50));
	particle1.addComponent<ParticleComponent>(Vector3(0, 0, 0));
	particle1.addComponent<ForceAccumulatorComponent>();
	particle1.addComponent<GravityForceComponent>();

	auto fSpring1 = world.createEntity();
	fSpring1.addComponent<TransformComponent>(Vector3(-10, 50, -50));
	fSpring1.addComponent<FixedSpringComponent>(10.0f, 20.0f, particle1);

	auto fSpring2 = world.createEntity();
	fSpring2.addComponent<TransformComponent>(Vector3(10, 55, -50));
	fSpring2.addComponent<FixedSpringComponent>(10.0f, 20.0f, particle1);

	auto particle2 = world.createEntity();
	particle2.addComponent<TransformComponent>(Vector3(-10, 20, -50));
	particle2.addComponent<ParticleComponent>(Vector3(0, 0, 0));
	particle2.addComponent<ForceAccumulatorComponent>();
	particle2.addComponent<GravityForceComponent>(0.1f);

	auto spring = world.createEntity();
	spring.addComponent<PairedSpringComponent>(10.0f, 15.0f, particle1, particle2);
}

void SphereSystem(ECSWorld& world)
{
	auto sphere = world.createEntity();
	sphere.addComponent<TransformComponent>(Vector3(0, 2, 0));
	sphere.addComponent<ParticleComponent>(Vector3(0, 40, 0));
	sphere.addComponent<ForceAccumulatorComponent>();
	sphere.addComponent<GravityForceComponent>();
	sphere.addComponent<ParticleSphereComponent>(2);

	auto sphere1 = world.createEntity();
	sphere1.addComponent<TransformComponent>(Vector3(0, 2, 0));
	sphere1.addComponent<ParticleComponent>(Vector3(RANDOM_FLOAT(-40, 40), 0, 0));
	sphere1.addComponent<ForceAccumulatorComponent>();
	sphere1.addComponent<GravityForceComponent>();
	sphere1.addComponent<ParticleSphereComponent>(2);

	auto sphere2 = world.createEntity();
	sphere2.addComponent<TransformComponent>(Vector3(0, 2, 0));
	sphere2.addComponent<ParticleComponent>(Vector3(0, 0, RANDOM_FLOAT(-40, 40)));
	sphere2.addComponent<ForceAccumulatorComponent>();
	sphere2.addComponent<GravityForceComponent>();
	sphere2.addComponent<ParticleSphereComponent>(2);
}

/***** Assignment 1 Part 1 method *****/
void Assignment1Part1(ECSWorld& world)
{
	auto pivot = world.createEntity();
	pivot.addComponent<TransformComponent>(Vector3(0, 10, 20));

	auto particle = world.createEntity();
	particle.addComponent<TransformComponent>(Vector3(0, -5, 20));
	particle.addComponent<ParticleComponent>(Vector3(0, 0, 0));
	particle.addComponent<ForceAccumulatorComponent>();
	particle.addComponent<GravityForceComponent>();
	particle.addComponent<BungeeEndComponent>();

	auto bungee = world.createEntity();
	bungee.addComponent<BungeeChordComponent>(10.0f, 10.0f, pivot, particle);
}

/***** Assignment 1 Part 2 method *****/
void Assignment1Part2(ECSWorld& world)
{
	auto particle = world.createEntity();
	particle.addComponent<TransformComponent>(Vector3(0, 20, 0));
	particle.addComponent<ParticleComponent>(Vector3(0, 0, 0));
	particle.addComponent<ForceAccumulatorComponent>();
	particle.addComponent<GravityForceComponent>();
	particle.addComponent<BuoyancyComponent>(Vector3(10, 10, 10), 5, 1);
	particle.addComponent<DragForceComponent>(0.2f, 0.1f);
}

/***** Assignment 1 Part 3 method *****/
void Assignment1Part3(ECSWorld& world)
{
	const float range = 30;

	for (int i = 0; i < 20; i++)
	{
		auto particle1 = world.createEntity();
		particle1.addComponent<TransformComponent>(Vector3(RANDOM_FLOAT(-range, range), RANDOM_FLOAT(-range, range), RANDOM_FLOAT(-range / 2, range / 2)));
		particle1.addComponent<ParticleComponent>(Vector3(0, 0, 0));
		particle1.addComponent<ForceAccumulatorComponent>(RANDOM_FLOAT(1, 10));
		particle1.addComponent<NBodyComponent>();
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
	hook.addComponent<TransformComponent>(Vector3(-14.5f - 1, 14, -61.5f - 1));
	hook = world.createEntity();
	hook.addComponent<TransformComponent>(Vector3(-14.5f - 0.25f, 14 - 0.5f, -61.5f + 1));
	hook = world.createEntity();
	hook.addComponent<TransformComponent>(Vector3(-14.5f + 0.5f, 14 + 1, -61.5f + 1));

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