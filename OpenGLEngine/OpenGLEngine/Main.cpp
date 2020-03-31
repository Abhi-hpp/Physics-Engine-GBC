//#define STB_IMAGE_IMPLEMENTATION
#include "RenderingSystem.h"
#include "RenderingSystemV2.h"
#include "InputEventSystem.h"
#include "FPSControlSystem.h"
#include "FollowCameraSystem.h"
#include "RotateSystem.h"
#include "RotateSystemV2.h"
#include "LifeTimeSystem.h"
#include "GravityForceSystem.h"
#include "DragForceSystem.h"
#include "FixedSpringSystem.h"
#include "PairedSpringSystem.h"
#include "ParticleContactResolutionSystem.h"
#include "ResetPenetrationDeltaMoveSystem.h"
#include "ForceAccumulatorSystem.h"
#include "ParticleSystem.h"
#include "RigidbodySystem.h"
#include "ForceAndTorqueAccumulatorSystem.h"
#include "DragSystem.h"
#include "AddTorqueFromCameraSystem.h"
#include "AeroControlSystem.h"
#include "AeroSurfaceSystem.h"
#include "ThrusterSystem.h"
#include "BuoyancyForceGeneratorSystem.h"
#include "WindThrusterSystem.h"
#include "DynamicDirectionalLightSystem.h"
#include "DynamicPointLightSystem.h"
#include "DynamicSpotLightSystem.h"
#include <string>
#include <stdlib.h>     
#include <time.h>      

using namespace Reality;

void LoadShaders(ECSWorld& world);
void LoadModels(ECSWorld& world);
void SetupLights(ECSWorld& world);
void MakeABunchaObjectsV2(ECSWorld& world);
void MakeRigidBodyTest(ECSWorld& world);
void MakeAFlightSimulator(ECSWorld& world);
void MakeBoatSimulator(ECSWorld& world);

void CreateShipSail(Reality::ECSWorld& world, Mix::Entity& shipEntity);

void CreateRudder(Reality::ECSWorld& world, Mix::Entity& shipEntity);

void CreateBuoyancies(Reality::ECSWorld& world, Mix::Entity& waterSurface, Mix::Entity& shipEntity);

void CreateShip(Mix::Entity& shipEntity);

int main()
{
	ECSWorld world;

	// Init and Load
	world.data.InitRendering();
	//LoadAssets(world);
	
	//world.data.renderUtil->camera.Position = Vector3(0, -190.0f, 80.0f);
	world.data.renderUtil->SetFOV(60);
	// Create entities

	// Make a player controller
	auto e = world.createEntity();
	e.addComponent<FPSControlComponent>();

	SetupLights(world);
	MakeBoatSimulator(world);

	// Create Systems
	world.getSystemManager().addSystem<RenderingSystem>();
	world.getSystemManager().addSystem<RenderingSystemV2>();
	world.getSystemManager().addSystem<InputEventSystem>();
	world.getSystemManager().addSystem<FPSControlSystem>();
	world.getSystemManager().addSystem<FollowCameraSystem>();
	world.getSystemManager().addSystem<RotateSystem>();
	world.getSystemManager().addSystem<RotateSystemV2>();
	world.getSystemManager().addSystem<LifeTimeSystem>();
	world.getSystemManager().addSystem<GravityForceSystem>();
	world.getSystemManager().addSystem<DragForceSystem>();
	world.getSystemManager().addSystem<FixedSpringSystem>();
	world.getSystemManager().addSystem<PairedSpringSystem>();
	world.getSystemManager().addSystem<ParticleContactResolutionSystem>();
	world.getSystemManager().addSystem<ResetPenetrationDeltaMoveSystem>();
	world.getSystemManager().addSystem<ForceAccumulatorSystem>();
	world.getSystemManager().addSystem<ParticleSystem>();
	world.getSystemManager().addSystem<RigidbodySystem>();
	world.getSystemManager().addSystem<BuoyancyForceGeneratorSystem>();
	world.getSystemManager().addSystem<ForceAndTorqueAccumulatorSystem>();
	world.getSystemManager().addSystem<DragSystem>();
	world.getSystemManager().addSystem<AddTorqueFromCameraSystem>();
	world.getSystemManager().addSystem<AeroControlSystem>();
	world.getSystemManager().addSystem<AeroSurfaceSystem>();
	world.getSystemManager().addSystem<ThrusterSystem>();
	world.getSystemManager().addSystem<WindThrusterSystem>();
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
		if(shadersLoaded && !modelsLoadStarted)
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
		world.getSystemManager().getSystem<FollowCameraSystem>().Update(deltaTime);
		world.getSystemManager().getSystem<RotateSystem>().Update(deltaTime);
		world.getSystemManager().getSystem<RotateSystemV2>().Update(deltaTime);
		world.getSystemManager().getSystem<LifeTimeSystem>().Update(deltaTime);
		world.getSystemManager().getSystem<AddTorqueFromCameraSystem>().Update(deltaTime);
		world.getSystemManager().getSystem<AeroControlSystem>().Update(deltaTime);

		// Update Transform

		// Physics
		//float fixedDeltaTime = glfwGetKey(world.data.renderUtil->window->glfwWindow, GLFW_KEY_SPACE) == GLFW_PRESS ? 1 / 60.0f : 0;		
		float fixedDeltaTime = 1 / 60.0f;
		// Force Generator
		/// Particle
		world.getSystemManager().getSystem<GravityForceSystem>().Update(fixedDeltaTime);
		world.getSystemManager().getSystem<DragForceSystem>().Update(fixedDeltaTime);
		world.getSystemManager().getSystem<FixedSpringSystem>().Update(fixedDeltaTime);
		world.getSystemManager().getSystem<PairedSpringSystem>().Update(fixedDeltaTime);

		/// Rigidbody
		world.getSystemManager().getSystem<DragSystem>().Update(fixedDeltaTime);
		world.getSystemManager().getSystem<AeroSurfaceSystem>().Update(fixedDeltaTime);
		world.getSystemManager().getSystem<ThrusterSystem>().Update(fixedDeltaTime);
		
		world.getSystemManager().getSystem<BuoyancyForceGeneratorSystem>().Update(fixedDeltaTime);
		world.getSystemManager().getSystem<WindThrusterSystem>().Update(fixedDeltaTime);

		// Force Accumulator
		/// Particle
		world.getSystemManager().getSystem<ForceAccumulatorSystem>().Update(fixedDeltaTime);

		/// Rigidbody
		world.getSystemManager().getSystem<ForceAndTorqueAccumulatorSystem>().Update(fixedDeltaTime);

		// Contact Resolution
		world.getSystemManager().getSystem<ParticleContactResolutionSystem>().Update(fixedDeltaTime);
		world.getSystemManager().getSystem<ResetPenetrationDeltaMoveSystem>().Update(fixedDeltaTime);

		// Integrator
		/// Particle
		world.getSystemManager().getSystem<ParticleSystem>().Update(fixedDeltaTime);

		/// Rigidbody
		world.getSystemManager().getSystem<RigidbodySystem>().Update(fixedDeltaTime);

		// Rendering Update
		///*** HACK: For the last DrawCall not working on some systems
		world.data.renderUtil->DrawCube(Vector3(0, 0, 0), Vector3(0, 0, 0));
		///*** HACK: For the last DrawCall not working on some systems
		world.getSystemManager().getSystem<DynamicDirectionalLightSystem>().Update(deltaTime);
		world.getSystemManager().getSystem<DynamicPointLightSystem>().Update(deltaTime);
		world.getSystemManager().getSystem<DynamicSpotLightSystem>().Update(deltaTime);
		world.getSystemManager().getSystem<RenderingSystem>().Update(deltaTime);
		world.getSystemManager().getSystem<RenderingSystemV2>().Update(deltaTime);

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
		ModelData("Resources/Models/Sponza-master/sponza.obj"),
		ModelData("Resources/Models/nanosuit/nanosuit.obj"),
		ModelData("Resources/Models/supermarine-spitfire/spitfire.fbx",
			{{"spitfire_d.png"}})
		});
}

void MakeABunchaObjectsV2(ECSWorld & world)
{
	auto flightV1 = world.createEntity();
	flightV1.addComponent<TransformComponent>(Vector3(-50, 0, -50), Vector3(0.1f, 0.1f, 0.1f), Vector3(270, 0, 0));
	// Add mesh
	flightV1.addComponent<ModelComponent>("Resources/Models/supermarine-spitfire/spitfire.fbx");
	flightV1.addComponent<RotateComponent>(Vector3(45, 70, -20));

	auto flightV2 = world.createEntity();
	flightV2.addComponent<TransformComponentV2>(Vector3(50, 0, -50), Vector3(0.1f, 0.1f, 0.1f), Vector3(270, 0, 0));
	// Add mesh
	flightV2.addComponent<ModelComponent>("Resources/Models/supermarine-spitfire/spitfire.fbx");
	flightV2.addComponent<RotateComponentV2>(Vector3(45, 70, -20));
}

void MakeRigidBodyTest(ECSWorld & world)
{
	auto flight = world.createEntity();
	flight.addComponent<TransformComponentV2>(Vector3(0, 0, -50), Vector3(0.1f, 0.1f, 0.1f));
	flight.addComponent<ModelComponent>("Resources/Models/supermarine-spitfire/spitfire.fbx", Vector3(-90, 0, 0), Vector3(0, -50, 0));
	flight.addComponent<RigidbodyComponent>();
	flight.addComponent<ForceAndTorqueAccumulatorComponent>();
	flight.addComponent<DragComponent>();
	flight.addComponent<AddTorqueFromCameraComponent>();
}

void MakeAFlightSimulator(ECSWorld & world)
{
	auto ground = world.createEntity();
	ground.addComponent<TransformComponentV2>(Vector3(0, -1000, 0), Vector3(10, 10, 10), Vector3(0, 90, 0));
	ground.addComponent<ModelComponent>("Resources/Models/Sponza-master/sponza.obj");
	
	auto flight = world.createEntity();
	flight.addComponent<TransformComponentV2>(Vector3(0, 0, -50), Vector3(0.1f, 0.1f, 0.1f), Vector3(0, 180, 0));
	flight.addComponent<ModelComponent>("Resources/Models/supermarine-spitfire/spitfire.fbx", Vector3(-90, 0, 0), Vector3(0, -50, 0));
	flight.addComponent<RigidbodyComponent>();
	flight.addComponent<ForceAndTorqueAccumulatorComponent>();
	flight.addComponent<DragComponent>(0.3, 0.5);
	flight.addComponent<FollowCameraComponent>();

	auto engine = world.createEntity();
	engine.addComponent<ThrusterComponent>(flight);

	auto leftWing = world.createEntity();
	leftWing.addComponent<TransformComponentV2>();
	leftWing.addComponent<AeroSurfaceComponent>(flight, Vector3(0, 0, 0), Vector3(100, 50, -50));
	std::vector<int> leftWingPositiveKeys = { GLFW_KEY_S, GLFW_KEY_Q };
	std::vector<int> leftWingNegetiveKeys = { GLFW_KEY_W, GLFW_KEY_E };
	leftWing.addComponent<AeroControlComponent>(
		Vector3(0, 0.1f, 0),
		Vector3(0, -0.1f, 0),
		leftWingPositiveKeys, leftWingNegetiveKeys);

	auto rightWing = world.createEntity();
	rightWing.addComponent<TransformComponentV2>();
	rightWing.addComponent<AeroSurfaceComponent>(flight, Vector3(0, 0, 0), Vector3(-100, 50, -50));
	std::vector<int> rightWingPositiveKeys = { GLFW_KEY_S, GLFW_KEY_E };
	std::vector<int> rightWingNegetiveKeys = { GLFW_KEY_W, GLFW_KEY_Q };
	rightWing.addComponent<AeroControlComponent>(
		Vector3(0, 0.1f, 0),
		Vector3(0, -0.1f, 0), 
		rightWingPositiveKeys, rightWingNegetiveKeys);

	auto rudder = world.createEntity();
	rudder.addComponent<TransformComponentV2>();
	rudder.addComponent<AeroSurfaceComponent>(flight, Vector3(0, 0, 0), Vector3(0, 0, -150));
	std::vector<int> rudderWingPositiveKeys = { GLFW_KEY_D };
	std::vector<int> rudderWingNegetiveKeys = { GLFW_KEY_A };
	rudder.addComponent<AeroControlComponent>(
		Vector3(-0.04f, 0, 0),
		Vector3(0.04f, 0, 0),
		rudderWingPositiveKeys, rudderWingNegetiveKeys);

}

void MakeBoatSimulator(ECSWorld & world)
{
	auto waterSurface = world.createEntity();
	waterSurface.addComponent<TransformComponentV2>(Vector3(0.0f, 0.0f, -30.0f), Vector3(50.0f, 50.0f, 50.0f));

	auto shipEntity = world.createEntity();
	CreateShip(shipEntity);

	CreateBuoyancies(world, waterSurface, shipEntity);

	CreateRudder(world, shipEntity);

	CreateShipSail(world, shipEntity);
}

void CreateShipSail(Reality::ECSWorld& world, Mix::Entity& shipEntity)
{
	auto shipSail = world.createEntity();
	shipSail.addComponent<WindThrusterComponent>(shipEntity, Vector3(0.0f, 0.0f, -1.0f), 1.0f, Vector3(0.0f, -20.0f, -55.0f));
}

void CreateRudder(Reality::ECSWorld& world, Mix::Entity& shipEntity)
{
	auto rudder = world.createEntity();
	rudder.addComponent<TransformComponentV2>();
	rudder.addComponent<AeroSurfaceComponent>(shipEntity, Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 30.0f, 220.0f));
	std::vector<int> rudderPositiveKeys = { GLFW_KEY_A };
	std::vector<int> rudderNegetiveKeys = { GLFW_KEY_D };
	rudder.addComponent<AeroControlComponent>(
		Vector3(-0.04f, 0.0f, 0.0f),
		Vector3(0.04f, 0.0f, 0.0f),
		rudderPositiveKeys, rudderNegetiveKeys);
}

void CreateBuoyancies(Reality::ECSWorld& world, Mix::Entity& waterSurface, Mix::Entity& shipEntity)
{
	auto buoyancyA = world.createEntity();
	buoyancyA.addComponent<TransformComponentV2>();
	buoyancyA.addComponent<ForceAndTorqueAccumulatorComponent>();
	buoyancyA.addComponent<BuoyancyForceGeneratorComponent>(5.0f, 2.0f, 3.0f, waterSurface, Vector3(0.0f, 0.0f, -130.0f), shipEntity);

	auto buoyancyB = world.createEntity();
	buoyancyB.addComponent<TransformComponentV2>();
	buoyancyB.addComponent<ForceAndTorqueAccumulatorComponent>();
	buoyancyB.addComponent<BuoyancyForceGeneratorComponent>(5.0f, 2.0f, 3.0f, waterSurface, Vector3(0.0f, 0.0f, 150.0f), shipEntity);
}

void CreateShip(Mix::Entity& shipEntity)
{
	shipEntity.addComponent<TransformComponentV2>(Vector3(0.0f, -3.0f, -30.0f), Vector3(0.1f, 0.1f, 0.1f), Vector3(0.0f, 0.0f, 0.0f));
	shipEntity.addComponent<ModelComponent>("Resources/Models/supermarine-spitfire/spitfire.fbx", Vector3(-90.0f, -180.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f));
	shipEntity.addComponent<RigidbodyComponent>();
	shipEntity.addComponent<ForceAndTorqueAccumulatorComponent>();
	shipEntity.addComponent<DragComponent>(0.5f, 0.5f);
	shipEntity.addComponent<FollowCameraComponent>();
}

void SetupLights(ECSWorld& world)
{
	auto l = world.createEntity();
	l.addComponent<TransformComponent>(Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(90, 0, 0));
	l.addComponent<DynamicDirectionalLightComponent>(Color(1, 1, 1), Color(0.0, 0.1, 0.1), Color(0.0, 0.1, 0.1));

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