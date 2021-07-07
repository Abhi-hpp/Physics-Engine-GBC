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
#include "BungeeChordSystem.h"
#include "PairedBungeeChordSystem.h"
#include "BuoyancySystem.h"
#include "NBodySystem.h"
#include "TriangleOfBridgeSystem.h"
#include "ParticleSphereSystem.h"
#include "CableSystem.h"
#include "RodSystem.h"
#include "ParticleContactResolutionSystem.h"
#include "ResetPenetrationDeltaMoveSystem.h"
#include "ForceAccumulatorSystem.h"
#include "ParticleSystem.h"
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
void MakeABunchaSpheres(ECSWorld& world);
void MakeABunchaCablesAndRods(ECSWorld& world);

/////////////////////For assignment Bungee chord///////////////////////////////
void MakeBungeeChord(ECSWorld& world);
void InputBungeeChord(ECSWorld& world);
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////For assignment Buoyancy///////////////////////////////
void MakeBuoyancy(ECSWorld& world);
void InputBuoyancy(ECSWorld& world);
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////For assignment NBody///////////////////////////////
void MakeNBody(ECSWorld& world);
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////For assignment2 Bridge///////////////////////////////
void MakeARopeBridge(ECSWorld& world);
void InputBridge(ECSWorld& world);
/////////////////////////////////////////////////////////////////////////////////////////////


bool bPressSpace = false;
bool bPressUp = false;
bool bPressDown = false;
ECSEntity lastConnectedParticle = ECSEntity();
ECSEntity BridgeColSphere;

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


	/////////////////////For assignment Bungee chord///////////////////////////////
	//MakeABunchaSprings(world);
	//MakeBungeeChord(world);
	/////////////////////////////////////////////////////////////////////////////////////////////

	/////////////////////For assignment Buoyancy///////////////////////////////
	//MakeBuoyancy(world);
	/////////////////////////////////////////////////////////////////////////////////////////////

	/////////////////////For assignment NBody///////////////////////////////
	//MakeNBody(world);
	/////////////////////////////////////////////////////////////////////////////////////////////

	//MakeABunchaSprings(world);
	//MakeABunchaSpheres(world);
	//MakeABunchaCablesAndRods(world);



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
	world.getSystemManager().addSystem<BungeeChordSystem>();
	world.getSystemManager().addSystem<PairedBungeeChordSystem>();
	world.getSystemManager().addSystem<BuoyancySystem>();
	world.getSystemManager().addSystem<NBodySystem>();
	world.getSystemManager().addSystem<TriangleOfBridgeSystem>();
	world.getSystemManager().addSystem<ParticleSphereSystem>();
	world.getSystemManager().addSystem<CableSystem>();
	world.getSystemManager().addSystem<RodSystem>();
	world.getSystemManager().addSystem<ParticleContactResolutionSystem>();
	world.getSystemManager().addSystem<ResetPenetrationDeltaMoveSystem>();
	world.getSystemManager().addSystem<ForceAccumulatorSystem>();
	world.getSystemManager().addSystem<ParticleSystem>();
	world.getSystemManager().addSystem<DynamicDirectionalLightSystem>();
	world.getSystemManager().addSystem<DynamicPointLightSystem>();
	world.getSystemManager().addSystem<DynamicSpotLightSystem>();

	/////////////////////For assignment2 Bridge///////////////////////////////
	MakeARopeBridge(world);
	/////////////////////////////////////////////////////////////////////////////////////////////

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


		/////////////////////For assignment Bungee chord///////////////////////////////
		//InputBungeeChord(world);
		/////////////////////////////////////////////////////////////////////////////////////////////

		/////////////////////For assignment Buoyancy///////////////////////////////
		//InputBuoyancy(world);
		/////////////////////////////////////////////////////////////////////////////////////////////
		
		/////////////////////For assignment2 Brideg///////////////////////////////
		InputBridge(world);
		/////////////////////////////////////////////////////////////////////////////////////////////

		// Game Logic Update
		world.getSystemManager().getSystem<FPSControlSystem>().Update(deltaTime);
		world.getSystemManager().getSystem<RotateSystem>().Update(deltaTime);
		world.getSystemManager().getSystem<FireworksSystem>().Update(deltaTime);
		world.getSystemManager().getSystem<ParticleSphereSystem>().Update(deltaTime);
		world.getSystemManager().getSystem<CableSystem>().Update(deltaTime);
		world.getSystemManager().getSystem<RodSystem>().Update(deltaTime);
		world.getSystemManager().getSystem<TriangleOfBridgeSystem>().Update(deltaTime);

		// Update Transform

		// Physics
		//float fixedDeltaTime = glfwGetKey(world.data.renderUtil->window->glfwWindow, GLFW_KEY_SPACE) == GLFW_PRESS ? 1 / 60.0f : 0;		
		float fixedDeltaTime = 1 / 60.0f;
		// Force Generator
		world.getSystemManager().getSystem<GravityForceSystem>().Update(fixedDeltaTime);
		world.getSystemManager().getSystem<DragForceSystem>().Update(fixedDeltaTime);
		world.getSystemManager().getSystem<FixedSpringSystem>().Update(fixedDeltaTime);
		world.getSystemManager().getSystem<PairedSpringSystem>().Update(fixedDeltaTime);
		world.getSystemManager().getSystem<BungeeChordSystem>().Update(fixedDeltaTime);
		world.getSystemManager().getSystem<PairedBungeeChordSystem>().Update(fixedDeltaTime);
		world.getSystemManager().getSystem<BuoyancySystem>().Update(fixedDeltaTime);
		world.getSystemManager().getSystem<NBodySystem>().Update(fixedDeltaTime);

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
	particle1.addComponent<TransformComponent>(Vector3(0, -5, 0));
	particle1.addComponent<ParticleComponent>(Vector3(0, 0, 0));
	particle1.addComponent<ForceAccumulatorComponent>();
	particle1.addComponent<GravityForceComponent>();

	/*auto particle2= world.createEntity();
	particle2.addComponent<TransformComponent>(Vector3(-10, 0, -50));
	particle2.addComponent<ParticleComponent>(Vector3(0, 0, 0));
	particle2.addComponent<ForceAccumulatorComponent>();
	particle2.addComponent<GravityForceComponent>();
*/
	auto spring1 = world.createEntity();
	spring1.addComponent<TransformComponent>(Vector3(0, 0, 0));
	spring1.addComponent<FixedSpringComponent>(10.0f, 20.0f, particle1);

	//auto spring2 = world.createEntity();
	//spring2.addComponent<TransformComponent>(Vector3(-10, 60, -50));
	//spring2.addComponent<FixedSpringComponent>(20.0f, 15.0f, particle1);

	//auto pairedSpring = world.createEntity();
	//pairedSpring.addComponent<PairedSpringComponent>(20.0f, 20.0f, particle1, particle2);
}

void MakeBungeeChord(ECSWorld& world)
{
	auto particle1 = world.createEntity();
	particle1.addComponent<TransformComponent>(Vector3(10, -5, 0));
	particle1.addComponent<ParticleComponent>(Vector3(0, 0, 0));
	particle1.addComponent<ForceAccumulatorComponent>();
	particle1.addComponent<GravityForceComponent>();

	auto particle2 = world.createEntity();
	particle2.addComponent<TransformComponent>(Vector3(15, -15, 0));
	particle2.addComponent<ParticleComponent>(Vector3(0, 0, 0));
	particle2.addComponent<ForceAccumulatorComponent>();
	particle2.addComponent<GravityForceComponent>();

	auto spring1 = world.createEntity();
	spring1.addComponent<TransformComponent>(Vector3(10, 0, 0));
	spring1.addComponent<BungeeChordComponent>(10.0f, 20.0f, particle1);

	auto pariedSpring = world.createEntity();
	pariedSpring.addComponent<PariedBungeeChordComponent>(10.0f, 20.0f, particle1, particle2);

	lastConnectedParticle = particle2;
}

void MakeBuoyancy(ECSWorld& world)
{
	for (int i = 0; i < 5; ++i)
	{
		auto particle1 = world.createEntity();
		particle1.addComponent<TransformComponent>(Vector3(RANDOM_FLOAT(-100, 100), RANDOM_FLOAT(-10, 10), RANDOM_FLOAT(-100, 100)));
		particle1.addComponent<ParticleComponent>(Vector3(0, 0, 0));
		particle1.addComponent<ForceAccumulatorComponent>();
		particle1.addComponent<GravityForceComponent>();
		particle1.addComponent<DragForceComponent>(1.f, 0.f);
		particle1.addComponent<BuoyancyComponent>(5.f, 2.f);
	}

}

void MakeNBody(ECSWorld& world)
{
	for (int i = 0; i < 30; ++i)
	{
		auto particle1 = world.createEntity();
		particle1.addComponent<TransformComponent>(Vector3(RANDOM_FLOAT(-10, 10), RANDOM_FLOAT(-10, 10), RANDOM_FLOAT(-10, 10)));
		particle1.addComponent<ParticleComponent>(Vector3(RANDOM_FLOAT(-1, 1), RANDOM_FLOAT(-1, 1), RANDOM_FLOAT(-1, 1)));
		particle1.addComponent<ForceAccumulatorComponent>();
		particle1.addComponent<NBodyComponent>(RANDOM_FLOAT(1, 4));
	}
}

void MakeABunchaSpheres(ECSWorld & world)
{
	for (int i = 0; i < 40; i++)
	{
		auto sphere = world.createEntity();
		sphere.addComponent<TransformComponent>(Vector3(RANDOM_FLOAT(-10, 10), RANDOM_FLOAT(-10, 10), RANDOM_FLOAT(-10, 10)));
		sphere.addComponent<ParticleComponent>(Vector3(RANDOM_FLOAT(-40, 40), RANDOM_FLOAT(-40, 40), RANDOM_FLOAT(-40, 40)));
		sphere.addComponent<ForceAccumulatorComponent>(1.0f);
		sphere.addComponent<GravityForceComponent>();
		sphere.addComponent<ParticleSphereComponent>(RANDOM_FLOAT(1, 3));
	}
}

void CreateParticleArchetype(ECSEntity e)
{
	e.addComponent<ParticleComponent>();
	e.addComponent<ForceAccumulatorComponent>();
	e.addComponent<GravityForceComponent>();
	//e.addComponent<ParticleSphereComponent>();
	e.addComponent<PenetrationDeltaMoveComponent>();
}

void MakeARopeBridge(ECSWorld & world)
{
	BridgeColSphere = world.createEntity();
	BridgeColSphere.addComponent<TransformComponent>(Vector3(20, 10, 0));
	BridgeColSphere.addComponent<ParticleComponent>();
	BridgeColSphere.addComponent<ForceAccumulatorComponent>(1.0f);
	BridgeColSphere.addComponent<GravityForceComponent>();
	BridgeColSphere.addComponent<PenetrationDeltaMoveComponent>();
	world.getSystemManager().getSystem<TriangleOfBridgeSystem>().SetSphere(BridgeColSphere);

	///////////////////////////////////1 Set/////////////////////////////////////
	//FIrst cable
	auto ePivot1 = world.createEntity();
	ePivot1.addComponent<TransformComponent>(Vector3(3, 10, 5));

	auto e1 = world.createEntity();
	e1.addComponent<TransformComponent>(Vector3(0, 3, 5));
	CreateParticleArchetype(e1);

	auto cable1 = world.createEntity();
	cable1.addComponent<CableComponent>(ePivot1, e1, 20, 1);


	//Second cable
	auto ePivot2 = world.createEntity();
	ePivot2.addComponent<TransformComponent>(Vector3(3, 10, -5));

	auto e2 = world.createEntity();
	e2.addComponent<TransformComponent>(Vector3(0, 2, -5));
	CreateParticleArchetype(e2);

	auto cable2 = world.createEntity();
	cable2.addComponent<CableComponent>(ePivot2, e2, 20, 1);


	//Connect first and second
	auto rod1 = world.createEntity();
	rod1.addComponent<RodComponent>(e1, e2, 10);
	///////////////////////////////////1 Set/////////////////////////////////////


	///////////////////////////////////2 Set/////////////////////////////////////
	//Third cable
	auto ePivot3 = world.createEntity();
	ePivot3.addComponent<TransformComponent>(Vector3(3 + 10, 10, 5));

	auto e3 = world.createEntity();
	e3.addComponent<TransformComponent>(Vector3(0 + 10, -2, 5));
	CreateParticleArchetype(e3);

	auto cable3 = world.createEntity();
	cable3.addComponent<CableComponent>(ePivot3, e3, 22, 1);


	//Fourth cable
	auto ePivot4 = world.createEntity();
	ePivot4.addComponent<TransformComponent>(Vector3(3 + 10, 10, -5));

	auto e4 = world.createEntity();
	e4.addComponent<TransformComponent>(Vector3(0 + 10, 0, -5));
	CreateParticleArchetype(e4);

	auto cable4 = world.createEntity();
	cable4.addComponent<CableComponent>(ePivot4, e4, 22, 1);

	//connect 3, 4
	auto rod2 = world.createEntity();
	rod2.addComponent<RodComponent>(e3, e4, 10);	
	///////////////////////////////////2 Set/////////////////////////////////////


	///////////////////////////////////connect 1, 2 Set/////////////////////////////////////
	//Connect 1, 3
	auto rod3 = world.createEntity();
	rod3.addComponent<RodComponent>(e1, e3, 10);
	//Connect 2, 4
	auto rod4 = world.createEntity();
	rod4.addComponent<RodComponent>(e2, e4, 10);
	//Connect 1, 4
	auto rod5 = world.createEntity();
	rod5.addComponent<RodComponent>(e1, e4, 10 * pow(2.0f, 0.5f));
	//Connect 2, 3
	auto rod6 = world.createEntity();
	rod6.addComponent<RodComponent>(e2, e3, 10 * pow(2.0f, 0.5f));

	//make triangle1
	auto tri1 = world.createEntity();
	tri1.addComponent<TriangleOfBridgeComponent>(e2, e1, e4);

	//make triangle2
	auto tri2 = world.createEntity();
	tri2.addComponent<TriangleOfBridgeComponent>(e3, e4, e1);
	///////////////////////////////////connect 1, 2 Set/////////////////////////////////////





	///////////////////////////////////3 Set/////////////////////////////////////
	//5 cable
	auto ePivot5 = world.createEntity();
	ePivot5.addComponent<TransformComponent>(Vector3(3 - 10, 10, 5));

	auto e5 = world.createEntity();
	e5.addComponent<TransformComponent>(Vector3(0 - 10, 1, 5));
	CreateParticleArchetype(e5);

	auto cable5 = world.createEntity();
	cable5.addComponent<CableComponent>(ePivot5, e5, 18, 1);

	//6 cable
	auto ePivot6 = world.createEntity();
	ePivot6.addComponent<TransformComponent>(Vector3(3 - 10, 10, -5));

	auto e6 = world.createEntity();
	e6.addComponent<TransformComponent>(Vector3(0 - 10, -1, -5));
	CreateParticleArchetype(e6);

	auto cable6 = world.createEntity();
	cable6.addComponent<CableComponent>(ePivot6, e6, 18, 1);

	//connect 5, 6
	auto rod7 = world.createEntity();
	rod7.addComponent<RodComponent>(e5, e6, 10);
	///////////////////////////////////3 Set/////////////////////////////////////


	///////////////////////////////////connect 1, 3 Set/////////////////////////////////////
	//connect 5, 1
	auto rod8 = world.createEntity();
	rod8.addComponent<RodComponent>(e5, e1, 10);
	//connect 6, 2
	auto rod9 = world.createEntity();
	rod9.addComponent<RodComponent>(e6, e2, 10);
	//connect 6, 1
	auto rod10 = world.createEntity();
	rod10.addComponent<RodComponent>(e6, e1, 10 * pow(2.0f, 0.5f));
	//connect 5, 2
	auto rod11 = world.createEntity();
	rod11.addComponent<RodComponent>(e5, e2, 10 * pow(2.0f, 0.5f));

	//make triangle3
	auto tri3 = world.createEntity();
	tri3.addComponent<TriangleOfBridgeComponent>(e6, e5, e2);

	//make triangle4
	auto tri4 = world.createEntity();
	tri4.addComponent<TriangleOfBridgeComponent>(e1, e2, e5);
	///////////////////////////////////connect 1, 3 Set/////////////////////////////////////


	///////////////////////////////////4 Set/////////////////////////////////////
	//7 cable
	auto ePivot7 = world.createEntity();
	ePivot7.addComponent<TransformComponent>(Vector3(3 + 20, 10, 5));

	auto e7 = world.createEntity();
	e7.addComponent<TransformComponent>(Vector3(0 + 20, 1, 5));
	CreateParticleArchetype(e7);

	auto cable7 = world.createEntity();
	cable7.addComponent<CableComponent>(ePivot7, e7, 22, 1);

	//8 cable
	auto ePivot8 = world.createEntity();
	ePivot8.addComponent<TransformComponent>(Vector3(3 + 20, 10, -5));

	auto e8 = world.createEntity();
	e8.addComponent<TransformComponent>(Vector3(0 + 20, -1, -5));
	CreateParticleArchetype(e8);

	auto cable8 = world.createEntity();
	cable8.addComponent<CableComponent>(ePivot8, e8, 22, 1);

	//connect 7, 8
	auto rod12 = world.createEntity();
	rod12.addComponent<RodComponent>(e7, e8, 10);
	///////////////////////////////////4 Set/////////////////////////////////////

	///////////////////////////////////connect 2, 4 Set/////////////////////////////////////
	//connect 3, 7
	auto rod13 = world.createEntity();
	rod13.addComponent<RodComponent>(e3, e7, 10);
	//connect 4, 8
	auto rod14 = world.createEntity();
	rod14.addComponent<RodComponent>(e4, e8, 10);
	//connect 3, 8
	auto rod15 = world.createEntity();
	rod15.addComponent<RodComponent>(e3, e8, 10 * pow(2.0f, 0.5f));
	//connect 4, 7
	auto rod16 = world.createEntity();
	rod16.addComponent<RodComponent>(e4, e7, 10 * pow(2.0f, 0.5f));

	//make triangle5
	auto tri5 = world.createEntity();
	tri5.addComponent<TriangleOfBridgeComponent>(e4, e3, e8);

	//make triangle6
	auto tri6 = world.createEntity();
	tri6.addComponent<TriangleOfBridgeComponent>(e7, e8, e3);
	///////////////////////////////////connect 2, 4 Set/////////////////////////////////////


	///////////////////////////////////5 Set/////////////////////////////////////
	//9 cable
	auto ePivot9 = world.createEntity();
	ePivot9.addComponent<TransformComponent>(Vector3(3 + 30, 10, 5));

	auto e9 = world.createEntity();
	e9.addComponent<TransformComponent>(Vector3(0 + 30, 1, 5));
	CreateParticleArchetype(e9);

	auto cable9 = world.createEntity();
	cable9.addComponent<CableComponent>(ePivot9, e9, 20, 1);

	//10 cable
	auto ePivot10 = world.createEntity();
	ePivot10.addComponent<TransformComponent>(Vector3(3 + 30, 10, -5));

	auto e10 = world.createEntity();
	e10.addComponent<TransformComponent>(Vector3(0 + 30, -1, -5));
	CreateParticleArchetype(e10);

	auto cable10 = world.createEntity();
	cable10.addComponent<CableComponent>(ePivot10, e10, 20, 1);

	//connect 9, 10
	auto rod17 = world.createEntity();
	rod17.addComponent<RodComponent>(e9, e10, 10);
	///////////////////////////////////5 Set/////////////////////////////////////


	///////////////////////////////////connect 4, 5 Set/////////////////////////////////////
	//connect 7, 9
	auto rod18 = world.createEntity();
	rod18.addComponent<RodComponent>(e7, e9, 10);
	//connect 8, 10
	auto rod19 = world.createEntity();
	rod19.addComponent<RodComponent>(e8, e10, 10);
	//connect 7, 10
	auto rod20 = world.createEntity();
	rod20.addComponent<RodComponent>(e7, e10, 10 * pow(2.0f, 0.5f));
	//connect 8, 9
	auto rod21 = world.createEntity();
	rod21.addComponent<RodComponent>(e8, e9, 10 * pow(2.0f, 0.5f));

	//make triangle7
	auto tri7 = world.createEntity();
	tri7.addComponent<TriangleOfBridgeComponent>(e8, e7, e10);

	//make triangle8
	auto tri8 = world.createEntity();
	tri8.addComponent<TriangleOfBridgeComponent>(e9, e10, e7);
	///////////////////////////////////connect 4, 5 Set/////////////////////////////////////


	///////////////////////////////////6 Set/////////////////////////////////////
	//11 cable
	auto ePivot11 = world.createEntity();
	ePivot11.addComponent<TransformComponent>(Vector3(3 + 40, 10, 5));

	auto e11 = world.createEntity();
	e11.addComponent<TransformComponent>(Vector3(0 + 40, 1, 5));
	CreateParticleArchetype(e11);

	auto cable11 = world.createEntity();
	cable11.addComponent<CableComponent>(ePivot11, e11, 18, 1);

	//12 cable
	auto ePivot12 = world.createEntity();
	ePivot12.addComponent<TransformComponent>(Vector3(3 + 40, 10, -5));

	auto e12 = world.createEntity();
	e12.addComponent<TransformComponent>(Vector3(0 + 40, -1, -5));
	CreateParticleArchetype(e12);

	auto cable12 = world.createEntity();
	cable12.addComponent<CableComponent>(ePivot12, e12, 18, 1);

	//connect 11, 12
	auto rod22 = world.createEntity();
	rod22.addComponent<RodComponent>(e11, e12, 10);
	///////////////////////////////////6 Set/////////////////////////////////////

	///////////////////////////////////connect 5, 6 Set/////////////////////////////////////
	//connect 9, 11
	auto rod23 = world.createEntity();
	rod23.addComponent<RodComponent>(e9, e11, 10);
	//connect 10, 12
	auto rod24 = world.createEntity();
	rod24.addComponent<RodComponent>(e10, e12, 10);
	//connect 9, 12
	auto rod25 = world.createEntity();
	rod25.addComponent<RodComponent>(e9, e12, 10 * pow(2.0f, 0.5f));
	//connect 10, 11
	auto rod26 = world.createEntity();
	rod26.addComponent<RodComponent>(e10, e11, 10 * pow(2.0f, 0.5f));

	//make triangle9
	auto tri9 = world.createEntity();
	tri9.addComponent<TriangleOfBridgeComponent>(e10, e9, e12);

	//make triangle10
	auto tri10 = world.createEntity();
	tri10.addComponent<TriangleOfBridgeComponent>(e11, e12, e9);
	///////////////////////////////////connect 5, 6 Set/////////////////////////////////////
}


void MakeABunchaCablesAndRods(ECSWorld & world)
{
	auto ePivot = world.createEntity();
	ePivot.addComponent<TransformComponent>(Vector3(3, 10, 0));

	auto e1 = world.createEntity();
	e1.addComponent<TransformComponent>(Vector3(0, 10, 0));
	e1.addComponent<ParticleComponent>();
	e1.addComponent<ForceAccumulatorComponent>();
	e1.addComponent<GravityForceComponent>();
	e1.addComponent<ParticleSphereComponent>();
	e1.addComponent<PenetrationDeltaMoveComponent>();

	auto e2 = world.createEntity();
	e2.addComponent<TransformComponent>(Vector3(5, 5, 0));
	e2.addComponent<ParticleComponent>();
	e2.addComponent<ForceAccumulatorComponent>();
	e2.addComponent<GravityForceComponent>();
	e2.addComponent<ParticleSphereComponent>();
	e2.addComponent<PenetrationDeltaMoveComponent>();

	auto e3 = world.createEntity();
	e3.addComponent<TransformComponent>(Vector3(0, 0, 0));
	e3.addComponent<ParticleComponent>();
	e3.addComponent<ForceAccumulatorComponent>();
	e3.addComponent<GravityForceComponent>();
	e3.addComponent<ParticleSphereComponent>();
	e3.addComponent<PenetrationDeltaMoveComponent>();

	auto e4 = world.createEntity();
	e4.addComponent<TransformComponent>(Vector3(-5, 5, 0));
	e4.addComponent<ParticleComponent>();
	e4.addComponent<ForceAccumulatorComponent>();
	e4.addComponent<GravityForceComponent>();
	e4.addComponent<ParticleSphereComponent>();
	e4.addComponent<PenetrationDeltaMoveComponent>();

	auto cable1 = world.createEntity();
	//cable.addComponent<CableComponent>(ePivot, e1, 5, 1);
	cable1.addComponent<PairedSpringComponent>(50, 2, ePivot, e1);

	auto cable2 = world.createEntity();
	//cable.addComponent<CableComponent>(ePivot, e1, 5, 1);
	cable2.addComponent<PairedSpringComponent>(50, 25, ePivot, e2);

	auto cable3 = world.createEntity();
	cable3.addComponent<CableComponent>(ePivot, e3, 15, 1);
	//cable3.addComponent<PairedSpringComponent>(50, 20, ePivot, e3);

	auto rod1 = world.createEntity();
	rod1.addComponent<RodComponent>(e1, e2, 5 * pow(2, 0.5f));

	auto rod2 = world.createEntity();
	rod2.addComponent<RodComponent>(e2, e3, 5 * pow(2, 0.5f));

	auto rod3 = world.createEntity();
	rod3.addComponent<RodComponent>(e3, e4, 5 * pow(2, 0.5f));

	auto rod4 = world.createEntity();
	rod4.addComponent<RodComponent>(e4, e1, 5 * pow(2, 0.5f));

	auto rod5 = world.createEntity();
	rod5.addComponent<RodComponent>(e1, e3, 10);

	auto rod6 = world.createEntity();
	rod6.addComponent<RodComponent>(e2, e4, 10);

	//for (int i = 0; i < 20; i++)
	//{
	//	auto e1 = world.createEntity();
	//	e1.addComponent<TransformComponent>(Vector3(RANDOM_FLOAT(-5, 5), RANDOM_FLOAT(-5, 5), RANDOM_FLOAT(-5, 5)));
	//	e1.addComponent<ParticleComponent>();
	//	e1.addComponent<ForceAccumulatorComponent>();
	//	e1.addComponent<GravityForceComponent>();
	//	e1.addComponent<ParticleSphereComponent>(RANDOM_FLOAT(0.5, 1.5));
	//	e1.addComponent<PenetrationDeltaMoveComponent>();

	//	auto e2 = world.createEntity();
	//	e2.addComponent<TransformComponent>(Vector3(RANDOM_FLOAT(-5, 5), RANDOM_FLOAT(-5, 5), RANDOM_FLOAT(-5, 5)));
	//	e2.addComponent<ParticleComponent>();
	//	e2.addComponent<ForceAccumulatorComponent>();
	//	e2.addComponent<GravityForceComponent>();
	//	e2.addComponent<ParticleSphereComponent>(RANDOM_FLOAT(0.5, 1.5));
	//	e2.addComponent<PenetrationDeltaMoveComponent>();

	//	auto rod = world.createEntity();
	//	rod.addComponent<RodComponent>(e1, e2, RANDOM_FLOAT(6, 10));
	//}
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

void InputBungeeChord(ECSWorld& world)
{
	GLFWwindow* window = world.data.renderUtil->window->glfwWindow;
	if ((glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) && bPressSpace == false)
	{
		bPressSpace = true;

		Camera& camera = world.data.renderUtil->camera;

		auto particle = world.createEntity();
		particle.addComponent<TransformComponent>(camera.Position + camera.Front);
		particle.addComponent<ParticleComponent>(Vector3(0, 0, 0));
		particle.addComponent<ForceAccumulatorComponent>();
		particle.addComponent<GravityForceComponent>();

		auto pairedSpring = world.createEntity();
		pairedSpring.addComponent<PariedBungeeChordComponent>(10.0f, 20.0f, lastConnectedParticle, particle);

		lastConnectedParticle = particle;
	}
	else if ((glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) && bPressSpace == true)
	{
		bPressSpace = false;
	}
}

void InputBuoyancy(ECSWorld& world)
{
	GLFWwindow* window = world.data.renderUtil->window->glfwWindow;
	if ((glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) && bPressSpace == false)
	{
		bPressSpace = true;

		Camera& camera = world.data.renderUtil->camera;
		Vector3 front = camera.Front;
		float dis = 20;
		front.x *= dis;
		front.y *= dis;
		front.z *= dis;
		auto particle1 = world.createEntity();
		particle1.addComponent<TransformComponent>(camera.Position + front);
		particle1.addComponent<ParticleComponent>(Vector3(0, 0, 0));
		particle1.addComponent<ForceAccumulatorComponent>();
		particle1.addComponent<GravityForceComponent>();
		particle1.addComponent<DragForceComponent>(1.f, 0.f);
		particle1.addComponent<BuoyancyComponent>(5.f, 2.f);
	}
	else if ((glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) && bPressSpace == true)
	{
		bPressSpace = false;
	}

	if ((glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) && bPressUp == false)
	{
		world.getSystemManager().getSystem<BuoyancySystem>().liquidDensity++;
		bPressUp = true;
	}
	else if ((glfwGetKey(window, GLFW_KEY_UP) == GLFW_RELEASE) && bPressUp == true)
	{
		bPressUp = false;
	}

	if ((glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) && bPressDown == false)
	{
		world.getSystemManager().getSystem<BuoyancySystem>().liquidDensity--;
		bPressDown = true;
	}
	else if ((glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_RELEASE) && bPressDown == true)
	{
		bPressDown = false;
	}
}

void InputBridge(ECSWorld& world)
{
	GLFWwindow* window = world.data.renderUtil->window->glfwWindow;
	if ((glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) && bPressSpace == false)
	{
		bPressSpace = true;

		Camera& camera = world.data.renderUtil->camera;
		Vector3 front = camera.Front;
		float dis = 20;
		front.x *= dis;
		front.y *= dis;
		front.z *= dis;
		
		world.destroyEntity(BridgeColSphere);
		BridgeColSphere = world.createEntity();
		BridgeColSphere.addComponent<TransformComponent>(camera.Position + front);
		BridgeColSphere.addComponent<ParticleComponent>();
		BridgeColSphere.addComponent<ForceAccumulatorComponent>(1.0f);
		BridgeColSphere.addComponent<GravityForceComponent>();
		BridgeColSphere.addComponent<PenetrationDeltaMoveComponent>();
		world.getSystemManager().getSystem<TriangleOfBridgeSystem>().SetSphere(BridgeColSphere);

	}
	else if ((glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) && bPressSpace == true)
	{
		bPressSpace = false;
	}
}
