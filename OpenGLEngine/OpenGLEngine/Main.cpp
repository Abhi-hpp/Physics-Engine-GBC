//#define STB_IMAGE_IMPLEMENTATION
#include "RenderingSystem.h"
#include "InputEventSystem.h"
#include "FPSControlSystem.h"
#include "RotateSystem.h"
#include "FireworksSystem.h"
#include "GravityForceSystem.h"
#include "DragForceSystem.h"
#include "FixedSpringSystem.h"
#include "PairedSpringSystem.h"
#include "ParticleSphereSystem.h"
#include "CableSystem.h"
#include "RodSystem.h"
#include "TriangleContactSystem.h"
#include "BungeeSystem.h"
#include "PairedBungeeSystem.h"
#include "BuoyancySystem.h"
#include "NBodySystem.h"
#include "ForceAccumulatorSystem.h"
#include "ParticleContactResolutionSystem.h"
#include "ResetPenetrationDeltaMoveSystem.h"
#include "ParticleSystem.h"
#include "ParticleSphereSystem.h"
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
void MakeABunchaObjects(ECSWorld& world);
void MakeFireworks(ECSWorld& world);
void Make3Particles(ECSWorld& world);
void MakeABunchaSprings(ECSWorld& world);
void MakeSpheres(ECSWorld& world);
void MakeBungee(ECSWorld& world);
void MakeBuoyancy(ECSWorld& world);
void MakeNBody(ECSWorld& world);
void MakePairedSprings(ECSWorld& world);
void MakeRopeBridge(ECSWorld& world);

void BridgeSpawnBall(ECSWorld& world);

ECSEntity BridgeBall;
bool eKeyPressed;

int main()
{
	ECSWorld world;

	// Init and Load
	world.data.InitRendering();
	//LoadAssets(world);
	
	world.data.renderUtil->camera.Position = Vector3(0, 0.0f, 50.0f);
	world.data.renderUtil->SetFOV(60);
	// Create entities

	// Make a player controller
	auto e = world.createEntity();
	e.addComponent<FPSControlComponent>();

	SetupLights(world);
	//MakeABunchaObjects(world);
	//MakeFireworks(world);
	//Make3Particles(world);
	//MakeABunchaSprings(world);
	//MakeSpheres(world);
	//MakePairedSprings(world);


	/// Assignment 1 Functions
	// Bungee Chord
	//MakeBungee(world);
	// Buoyancy
	//MakeBuoyancy(world);
	// N-Body
	//MakeNBody(world);

	/// Assignment 2 Functions
	// Construct Bridge
	MakeRopeBridge(world);

	// Create Systems
	world.getSystemManager().addSystem<RenderingSystem>();
	world.getSystemManager().addSystem<InputEventSystem>();
	world.getSystemManager().addSystem<FPSControlSystem>();
	world.getSystemManager().addSystem<RotateSystem>();
	world.getSystemManager().addSystem<FireworksSystem>();
	world.getSystemManager().addSystem<GravityForceSystem>();
	world.getSystemManager().addSystem<DragForceSystem>();
	world.getSystemManager().addSystem<FixedSpringSystem>();
	world.getSystemManager().addSystem<PairedSpringSystem>();
	world.getSystemManager().addSystem<BungeeSystem>(); // Bungee System
	world.getSystemManager().addSystem<PairedBungeeSystem>(); // Paired Bungee System
	world.getSystemManager().addSystem<BuoyancySystem>(); // Buoyancy System
	world.getSystemManager().addSystem<NBodySystem>(); // NBody System
	world.getSystemManager().addSystem<CableSystem>();
	world.getSystemManager().addSystem<RodSystem>();
	world.getSystemManager().addSystem<TriangleContactSystem>(); // Triangle Contact System
	world.getSystemManager().addSystem<ResetPenetrationDeltaMoveSystem>();
	world.getSystemManager().addSystem<ForceAccumulatorSystem>();
	world.getSystemManager().addSystem<ParticleContactResolutionSystem>();
	world.getSystemManager().addSystem<ParticleSystem>();
	world.getSystemManager().addSystem<ParticleSphereSystem>();
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

		// BungeeInput
		// BuoyancyInput
		BridgeSpawnBall(world);

		// Game Logic Update
		world.getSystemManager().getSystem<FPSControlSystem>().Update(deltaTime);
		world.getSystemManager().getSystem<RotateSystem>().Update(deltaTime);
		world.getSystemManager().getSystem<FireworksSystem>().Update(deltaTime);
		world.getSystemManager().getSystem<ParticleSphereSystem>().Update(deltaTime); // Commented out to remove red cube.
		world.getSystemManager().getSystem<CableSystem>().Update(deltaTime);
		world.getSystemManager().getSystem<RodSystem>().Update(deltaTime);
		world.getSystemManager().getSystem<TriangleContactSystem>().Update(deltaTime);

		// Update Transform

		// Physics
		//float fixedDeltaTime = glfwGetKey(world.data.renderUtil->window->glfwWindow, GLFW_KEY_SPACE) == GLFW_PRESS ? 1 / 60.0f : 0;		
		float fixedDeltaTime = 1 / 60.0f;
		// Force Generator
		world.getSystemManager().getSystem<GravityForceSystem>().Update(fixedDeltaTime);
		world.getSystemManager().getSystem<DragForceSystem>().Update(fixedDeltaTime);
		world.getSystemManager().getSystem<FixedSpringSystem>().Update(fixedDeltaTime);
		world.getSystemManager().getSystem<PairedSpringSystem>().Update(fixedDeltaTime);
		world.getSystemManager().getSystem<BungeeSystem>().Update(fixedDeltaTime); // Bungee system
		world.getSystemManager().getSystem<PairedBungeeSystem>().Update(fixedDeltaTime); // Paired Bungee system
		world.getSystemManager().getSystem<BuoyancySystem>().Update(fixedDeltaTime); // Buoyancy system
		world.getSystemManager().getSystem<NBodySystem>().Update(fixedDeltaTime); // NBody system

		// Force Accumulator
		world.getSystemManager().getSystem<ForceAccumulatorSystem>().Update(fixedDeltaTime);

		// Contact Resolution
		world.getSystemManager().getSystem<ParticleContactResolutionSystem>().Update(fixedDeltaTime);
		world.getSystemManager().getSystem<ResetPenetrationDeltaMoveSystem>().Update(fixedDeltaTime);

		// Integrator
		world.getSystemManager().getSystem<ParticleSystem>().Update(fixedDeltaTime);

		// Rendering Update
		///*** HACK: For the last DrawCall not working on some systems
		world.data.renderUtil->DrawCube(Vector3(0, 0, 0), Vector3(0, 0, 0));
		///*** HACK: For the last DrawCall not working on some systems
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

void Make3Particles(ECSWorld & world)
{
	auto particle1 = world.createEntity();
	particle1.addComponent<TransformComponent>(Vector3(-10, 60, -50));
	particle1.addComponent<ParticleComponent>(Vector3(0, 0, 0));
	particle1.addComponent<ForceAccumulatorComponent>();
	particle1.addComponent<GravityForceComponent>();
	particle1.addComponent<DragForceComponent>(0, 0);

	auto particle2 = world.createEntity();
	particle2.addComponent<TransformComponent>(Vector3(0, 60, -50));
	particle2.addComponent<ParticleComponent>(Vector3(0, 0, 0));
	particle2.addComponent<ForceAccumulatorComponent>();
	particle2.addComponent<GravityForceComponent>();
	particle2.addComponent<DragForceComponent>(1, 0);

	auto particle3 = world.createEntity();
	particle3.addComponent<TransformComponent>(Vector3(10, 60, -50));
	particle3.addComponent<ParticleComponent>(Vector3(0, 0, 0));
	particle3.addComponent<ForceAccumulatorComponent>();
	particle3.addComponent<GravityForceComponent>();
	particle3.addComponent<DragForceComponent>(1, 1);
}

void MakeABunchaSprings(ECSWorld & world)
{
	auto particle1 = world.createEntity();
	particle1.addComponent<TransformComponent>(Vector3(0, 20, -50));
	particle1.addComponent<ParticleComponent>(Vector3(0, 0, 0));
	particle1.addComponent<ForceAccumulatorComponent>();
	particle1.addComponent<GravityForceComponent>();

	auto spring1 = world.createEntity();
	spring1.addComponent<TransformComponent>(Vector3(10, 60, -50));
	spring1.addComponent<FixedSpringComponent>(10.0f, 10.0f, particle1);

	//auto particle2= world.createEntity();
	//particle2.addComponent<TransformComponent>(Vector3(-10, 0, -50));
	//particle2.addComponent<ParticleComponent>(Vector3(0, 0, 0));
	//particle2.addComponent<ForceAccumulatorComponent>();
	//particle2.addComponent<GravityForceComponent>();

	//auto spring1 = world.createEntity();
	//spring1.addComponent<TransformComponent>(Vector3(10, 60, -50));
	//spring1.addComponent<FixedSpringComponent>(20.0f, 20.0f, particle1);

	//auto spring2 = world.createEntity();
	//spring2.addComponent<TransformComponent>(Vector3(-10, 60, -50));
	//spring2.addComponent<FixedSpringComponent>(20.0f, 15.0f, particle1);

	//auto pairedSpring = world.createEntity();
	//pairedSpring.addComponent<PairedSpringComponent>(20.0f, 20.0f, particle1, particle2);

}

void MakeSpheres(ECSWorld & world)
{
	auto sphere = world.createEntity();
	sphere.addComponent<ParticleSphereComponent>();
	sphere.addComponent<TransformComponent>(Vector3(0, 0, 0));
	sphere.addComponent<ParticleComponent>(Vector3(RANDOM_FLOAT(-40, 40), RANDOM_FLOAT(-40, 40), RANDOM_FLOAT(-40, 40)));
	sphere.addComponent<ForceAccumulatorComponent>(1.0f);
	sphere.addComponent<GravityForceComponent>();
}

void MakeBungee(ECSWorld & world)
{
	//auto staticParticle = world.createEntity();
	//staticParticle.addComponent<TransformComponent>(Vector3(-60, 40, -50));
	//staticParticle.addComponent<ParticleComponent>(Vector3(0, 0, 0));
	//staticParticle.addComponent<ForceAccumulatorComponent>();

	auto particle1 = world.createEntity();
	particle1.addComponent<TransformComponent>(Vector3(0, 30, -50));
	particle1.addComponent<ParticleComponent>(Vector3(0, 0, 0));
	particle1.addComponent<ForceAccumulatorComponent>();
	particle1.addComponent<GravityForceComponent>();

	auto particle2 = world.createEntity();
	particle2.addComponent<TransformComponent>(Vector3(30, 20, -50));
	particle2.addComponent<ParticleComponent>(Vector3(0, 0, 0));
	particle2.addComponent<ForceAccumulatorComponent>();
	particle2.addComponent<GravityForceComponent>();

	auto bungee1 = world.createEntity();
	bungee1.addComponent<TransformComponent>(Vector3(-10, 30, -50));
	bungee1.addComponent<BungeeComponent>(10.0f, 10.0f, particle1);

	auto spring1 = world.createEntity();
	spring1.addComponent<TransformComponent>(Vector3(30, 40, -50));
	spring1.addComponent<BungeeComponent>(10.0f, 10.0f, particle2);

	auto pairedBungee1 = world.createEntity();
	pairedBungee1.addComponent<PairedBungeeComponent>(10.0f, 10.0f, particle1, particle2);
}

void MakeBuoyancy(ECSWorld & world)
{
	auto particle1 = world.createEntity();
	particle1.addComponent<TransformComponent>(Vector3(0.0f, 40.0f, 0.0f));
	particle1.addComponent<ParticleComponent>(Vector3(0.0f, 0.0f, 0.0f));
	particle1.addComponent<ForceAccumulatorComponent>();
	particle1.addComponent<GravityForceComponent>();
	particle1.addComponent<DragForceComponent>(1.0f, 0.0f);
	particle1.addComponent<BuoyancyComponent>(1.0f, 3.5f);

	auto particle2 = world.createEntity();
	particle2.addComponent<TransformComponent>(Vector3(-10.0f, 100.0f, 0.0f));
	particle2.addComponent<ParticleComponent>(Vector3(0.0f, 0.0f, 0.0f));
	particle2.addComponent<ForceAccumulatorComponent>();
	particle2.addComponent<GravityForceComponent>();
	particle2.addComponent<DragForceComponent>(1.0f, 0.0f);
	particle2.addComponent<BuoyancyComponent>(1.0f, 3.5f); 

	auto particle3 = world.createEntity();
	particle3.addComponent<TransformComponent>(Vector3(10.0f, 120.0f, 0.0f));
	particle3.addComponent<ParticleComponent>(Vector3(0.0f, 0.0f, 0.0f));
	particle3.addComponent<ForceAccumulatorComponent>();
	particle3.addComponent<GravityForceComponent>();
	particle3.addComponent<DragForceComponent>(1.0f, 0.0f);
	particle3.addComponent<BuoyancyComponent>(1.0f, 3.5f); 

	auto particle4 = world.createEntity();
	particle4.addComponent<TransformComponent>(Vector3(5.0f, 110.0f, -10.0f));
	particle4.addComponent<ParticleComponent>(Vector3(0.0f, 0.0f, 0.0f));
	particle4.addComponent<ForceAccumulatorComponent>();
	particle4.addComponent<GravityForceComponent>();
	particle4.addComponent<DragForceComponent>(1.0f, 0.0f);
	particle4.addComponent<BuoyancyComponent>(1.0f, 3.5f);

	auto particle5 = world.createEntity();
	particle5.addComponent<TransformComponent>(Vector3(-5.0f, 150.0f, -10.0f));
	particle5.addComponent<ParticleComponent>(Vector3(0.0f, 0.0f, 0.0f));
	particle5.addComponent<ForceAccumulatorComponent>();
	particle5.addComponent<GravityForceComponent>();
	particle5.addComponent<DragForceComponent>(1.0f, 0.0f);
	particle5.addComponent<BuoyancyComponent>(1.0f, 3.5f);

}

void MakeNBody(ECSWorld & world)
{
	auto particle1 = world.createEntity();
	particle1.addComponent<TransformComponent>(Vector3(0, 0, 0));
	particle1.addComponent<ParticleComponent>(Vector3(0, 1, 0));
	particle1.addComponent<ForceAccumulatorComponent>();
	particle1.addComponent<NBodyComponent>(10);

	auto particle2 = world.createEntity();
	particle2.addComponent<TransformComponent>(Vector3(-20, 0, 0));
	particle2.addComponent<ParticleComponent>(Vector3(1, 0, 0));
	particle2.addComponent<ForceAccumulatorComponent>();
	particle2.addComponent<NBodyComponent>(25);

	auto particle3 = world.createEntity();
	particle3.addComponent<TransformComponent>(Vector3(-20, 20, 0));
	particle3.addComponent<ParticleComponent>(Vector3(1, -1, 0));
	particle3.addComponent<ForceAccumulatorComponent>();
	particle3.addComponent<NBodyComponent>(65);

	auto particle4 = world.createEntity();
	particle4.addComponent<TransformComponent>(Vector3(0, 20, 0));
	particle4.addComponent<ParticleComponent>(Vector3(0, -1, 0));
	particle4.addComponent<ForceAccumulatorComponent>();
	particle4.addComponent<NBodyComponent>(98);

	auto particle5 = world.createEntity();
	particle5.addComponent<TransformComponent>(Vector3(20, 20, 0));
	particle5.addComponent<ParticleComponent>(Vector3(-1, -1, 0));
	particle5.addComponent<ForceAccumulatorComponent>();
	particle5.addComponent<NBodyComponent>(32);

	auto particle6 = world.createEntity();
	particle6.addComponent<TransformComponent>(Vector3(20, 0, 0));
	particle6.addComponent<ParticleComponent>(Vector3(-1, 0, 0));
	particle6.addComponent<ForceAccumulatorComponent>();
	particle6.addComponent<NBodyComponent>(44);

	auto particle7 = world.createEntity();
	particle7.addComponent<TransformComponent>(Vector3(20, -20, 0));
	particle7.addComponent<ParticleComponent>(Vector3(-1, 1, 0));
	particle7.addComponent<ForceAccumulatorComponent>();
	particle7.addComponent<NBodyComponent>(61);

	auto particle8 = world.createEntity();
	particle8.addComponent<TransformComponent>(Vector3(0, -20, 0));
	particle8.addComponent<ParticleComponent>(Vector3(0, 1, 0));
	particle8.addComponent<ForceAccumulatorComponent>();
	particle8.addComponent<NBodyComponent>(73);

	auto particle9 = world.createEntity();
	particle9.addComponent<TransformComponent>(Vector3(-20, -20, 0));
	particle9.addComponent<ParticleComponent>(Vector3(1, 1, 0));
	particle9.addComponent<ForceAccumulatorComponent>();
	particle9.addComponent<NBodyComponent>(4);

	auto particle10 = world.createEntity();
	particle10.addComponent<TransformComponent>(Vector3(5, 0, 0));
	particle10.addComponent<ParticleComponent>(Vector3(-1, 0, 0));
	particle10.addComponent<ForceAccumulatorComponent>();
	particle10.addComponent<NBodyComponent>(103);
}

void MakePairedSprings(ECSWorld & world)
{
	auto particle1 = world.createEntity();
	particle1.addComponent<TransformComponent>(Vector3(0, 20, -50));
	particle1.addComponent<ParticleComponent>(Vector3(0, 0, 0));
	particle1.addComponent<ForceAccumulatorComponent>();
	particle1.addComponent<GravityForceComponent>();

	auto fixedSpring1 = world.createEntity();
	fixedSpring1.addComponent<TransformComponent>(Vector3(0, 40, -50));
	fixedSpring1.addComponent<FixedSpringComponent>(10.0f, 10.0f, particle1);

	auto fixedSpring3 = world.createEntity();
	fixedSpring3.addComponent<TransformComponent>(Vector3(0, 10, -50));
	fixedSpring3.addComponent<FixedSpringComponent>(10.0f, 10.0f, particle1);


	auto particle2 = world.createEntity();
	particle2.addComponent<TransformComponent>(Vector3(30, 30, -50));
	particle2.addComponent<ParticleComponent>(Vector3(0, 0, 0));
	particle2.addComponent<ForceAccumulatorComponent>();
	particle2.addComponent<GravityForceComponent>();

	auto fixedSpring2 = world.createEntity();
	fixedSpring2.addComponent<TransformComponent>(Vector3(30, 40, -50));
	fixedSpring2.addComponent<FixedSpringComponent>(1.0f, 10.0f, particle2);
}

void CreateParticleArchetype(ECSEntity e)
{
	e.addComponent<ParticleComponent>();
	e.addComponent<ForceAccumulatorComponent>();
	e.addComponent<GravityForceComponent>();
	//e.addComponent<ParticleSphereComponent>();
	e.addComponent<PenetrationDeltaMoveComponent>();
}

void BridgeSpawnBall(ECSWorld& world)
{
	GLFWwindow* window = world.data.renderUtil->window->glfwWindow;

	if ((glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS))
	{
		// Destroy previous ball
		world.destroyEntity(BridgeBall);

		//world.getSystemManager().getSystem<TriangleContactSystem>().sphereCreated = false;

		// Spawn new ball with random x position above bridge
		BridgeBall = world.createEntity();
		BridgeBall.addComponent<TransformComponent>(Vector3(RANDOM_FLOAT(-35, 0), 8, -0.0));
		BridgeBall.addComponent<ParticleComponent>();
		BridgeBall.addComponent<ForceAccumulatorComponent>(1.0f);
		BridgeBall.addComponent<GravityForceComponent>();
		BridgeBall.addComponent<PenetrationDeltaMoveComponent>();
		world.getSystemManager().getSystem<TriangleContactSystem>().CreateSphere(BridgeBall);
	}
}

void MakeRopeBridge(ECSWorld & world)
{
	BridgeBall = world.createEntity();
	//world.getSystemManager().getSystem<TriangleContactSystem>().CreateSphere(BridgeBall);

	auto ePivot1 = world.createEntity();
	ePivot1.addComponent<TransformComponent>(Vector3(3, 10, 5));

	auto e1 = world.createEntity();
	e1.addComponent<TransformComponent>(Vector3(0, -3, 5));
	CreateParticleArchetype(e1);

	auto ePivot2 = world.createEntity();
	ePivot2.addComponent<TransformComponent>(Vector3(3, 10, -5));

	auto e2 = world.createEntity();
	e2.addComponent<TransformComponent>(Vector3(0, -3, -5));
	CreateParticleArchetype(e2);

	auto rod1 = world.createEntity();
	rod1.addComponent<RodComponent>(e1, e2, 10);

	auto cable1 = world.createEntity();
	cable1.addComponent<CableComponent>(ePivot1, e1, 15, 1);

	auto cable2 = world.createEntity();
	cable2.addComponent<CableComponent>(ePivot2, e2, 15, 1);

	// 2
	auto ePivot3 = world.createEntity();
	ePivot3.addComponent<TransformComponent>(Vector3(-10, 10, 5));

	auto e3 = world.createEntity();
	e3.addComponent<TransformComponent>(Vector3(-10, -3, 5));
	CreateParticleArchetype(e3);

	auto ePivot4 = world.createEntity();
	ePivot4.addComponent<TransformComponent>(Vector3(-10, 10, -5));

	auto e4 = world.createEntity();
	e4.addComponent<TransformComponent>(Vector3(-10, -3, -5));
	CreateParticleArchetype(e4);

	auto rod2 = world.createEntity();
	rod2.addComponent<RodComponent>(e3, e4, 10);

	auto cable3 = world.createEntity();
	cable3.addComponent<CableComponent>(ePivot3, e3, 20, 1);

	auto cable4 = world.createEntity();
	cable4.addComponent<CableComponent>(ePivot4, e4, 20, 1);

	// 3
	auto ePivot5 = world.createEntity();
	ePivot5.addComponent<TransformComponent>(Vector3(-20, 10, 5));

	auto e5 = world.createEntity();
	e5.addComponent<TransformComponent>(Vector3(-20, -8, 5));
	CreateParticleArchetype(e5);

	auto ePivot6 = world.createEntity();
	ePivot6.addComponent<TransformComponent>(Vector3(-20, 10, -5));

	auto e6 = world.createEntity();
	e6.addComponent<TransformComponent>(Vector3(-20, -8, -5));
	CreateParticleArchetype(e6);

	auto rod3 = world.createEntity();
	rod3.addComponent<RodComponent>(e5, e6, 10);

	auto cable5 = world.createEntity();
	cable5.addComponent<CableComponent>(ePivot5, e5, 21, 1);

	auto cable6 = world.createEntity();
	cable6.addComponent<CableComponent>(ePivot6, e6, 21, 1);

	// 4
	auto ePivot7 = world.createEntity();
	ePivot7.addComponent<TransformComponent>(Vector3(-30, 10, 5));

	auto e7 = world.createEntity();
	e7.addComponent<TransformComponent>(Vector3(-30, -3, 5));
	CreateParticleArchetype(e7);

	auto ePivot8 = world.createEntity();
	ePivot8.addComponent<TransformComponent>(Vector3(-30, 10, -5));

	auto e8 = world.createEntity();
	e8.addComponent<TransformComponent>(Vector3(-30, -3, -5));
	CreateParticleArchetype(e8);

	auto rod4 = world.createEntity();
	rod4.addComponent<RodComponent>(e7, e8, 10);

	auto cable7 = world.createEntity();
	cable7.addComponent<CableComponent>(ePivot7, e7, 20, 1);

	auto cable8 = world.createEntity();
	cable8.addComponent<CableComponent>(ePivot8, e8, 20, 1);

	// 5
	auto ePivot9 = world.createEntity();
	ePivot9.addComponent<TransformComponent>(Vector3(-40, 10, 5));

	auto e9 = world.createEntity();
	e9.addComponent<TransformComponent>(Vector3(-40, -3, 5));
	CreateParticleArchetype(e9);

	auto ePivot10 = world.createEntity();
	ePivot10.addComponent<TransformComponent>(Vector3(-40, 10, -5));

	auto e10 = world.createEntity();
	e10.addComponent<TransformComponent>(Vector3(-40, -3, -5));
	CreateParticleArchetype(e10);

	auto rod5 = world.createEntity();
	rod5.addComponent<RodComponent>(e9, e10, 10);

	auto cable9 = world.createEntity();
	cable9.addComponent<CableComponent>(ePivot9, e9, 15, 1);

	auto cable10 = world.createEntity();
	cable10.addComponent<CableComponent>(ePivot10, e10, 15, 1);

	// Rods
	auto rod6 = world.createEntity();
	rod6.addComponent<RodComponent>(e1, e3, 10);
	auto rod7 = world.createEntity();
	rod7.addComponent<RodComponent>(e2, e4, 10);
	auto rod8 = world.createEntity();
	rod8.addComponent<RodComponent>(e3, e5, 10);
	auto rod9 = world.createEntity();
	rod9.addComponent<RodComponent>(e4, e6, 10);
	auto rod10 = world.createEntity();
	rod10.addComponent<RodComponent>(e5, e7, 10);
	auto rod11 = world.createEntity();
	rod11.addComponent<RodComponent>(e6, e8, 10);
	auto rod12 = world.createEntity();
	rod12.addComponent<RodComponent>(e7, e9, 10);
	auto rod13 = world.createEntity();
	rod13.addComponent<RodComponent>(e8, e10, 10);

	// Diagonal rods
	auto rod14 = world.createEntity();
	rod14.addComponent<RodComponent>(e1, e4, 10 * pow(2.0f, 0.5f));
	auto rod15 = world.createEntity();
	rod15.addComponent<RodComponent>(e2, e3, 10 * pow(2.0f, 0.5f));
	auto rod16 = world.createEntity();
	rod16.addComponent<RodComponent>(e3, e6, 10 * pow(2.0f, 0.5f));
	auto rod17 = world.createEntity();
	rod17.addComponent<RodComponent>(e4, e5, 10 * pow(2.0f, 0.5f));
	auto rod18 = world.createEntity();
	rod18.addComponent<RodComponent>(e5, e8, 10 * pow(2.0f, 0.5f));
	auto rod19 = world.createEntity();
	rod19.addComponent<RodComponent>(e6, e7, 10 * pow(2.0f, 0.5f));
	auto rod20 = world.createEntity();
	rod20.addComponent<RodComponent>(e7, e10, 10 * pow(2.0f, 0.5f));
	auto rod21 = world.createEntity();
	rod21.addComponent<RodComponent>(e8, e9, 10 * pow(2.0f, 0.5f));

	// Triangles
	auto triangle1 = world.createEntity();
	triangle1.addComponent<TriangleComponent>(e1, e2, e4);
	auto triangle2 = world.createEntity();
	triangle2.addComponent<TriangleComponent>(e1, e4, e3);
	auto triangle3 = world.createEntity();
	triangle3.addComponent<TriangleComponent>(e3, e4, e6);
	auto triangle4 = world.createEntity();
	triangle4.addComponent<TriangleComponent>(e3, e6, e5);
	auto triangle5 = world.createEntity();
	triangle5.addComponent<TriangleComponent>(e5, e6, e8);
	auto triangle6 = world.createEntity();
	triangle6.addComponent<TriangleComponent>(e5, e8, e7);
	auto triangle7 = world.createEntity();
	triangle7.addComponent<TriangleComponent>(e7, e8, e10);
	auto triangle8 = world.createEntity();
	triangle8.addComponent<TriangleComponent>(e7, e10, e9);
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