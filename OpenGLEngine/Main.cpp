// PHYSICS ENGINE Team "Getters & Setters" submission.
// ASSIGNMENT 2 by Amer Ali Mohammed (ID: 101206769), Talhah Ramadan Salick (ID: 101214166) and Jeremy Evans (ID: 101221919)
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
#include "BridgeRopeSystem.h"
#include "BridgeRodSystem.h"
#include "ParticleCollisionResolvingSystem.h"
#include "PenetrationMovementResetSystem.h"
#include "ForceAccumulatorSystem.h"
#include "ParticleSystem.h"
#include "FloorCollideSystem.h"
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
void MakeRopeBridge(ECSWorld& world);

bool pressed;
bool spawnBall = false;
void input(ECSWorld& world);
int testBalls = 0;
string tag = to_string(testBalls);

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
	//MakeABunchaSpheres(world);
	//MakeABunchaCablesAndRods(world);
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
	world.getSystemManager().addSystem<ParticleSphereSystem>();
	world.getSystemManager().addSystem<BridgeRopeSystem>();
	world.getSystemManager().addSystem<BridgeRodSystem>();
	world.getSystemManager().addSystem<ParticleCollisionResolvingSystem>();
	world.getSystemManager().addSystem<PenetrationMovementResetSystem>();
	world.getSystemManager().addSystem<ForceAccumulatorSystem>();
	world.getSystemManager().addSystem<ParticleSystem>();
	world.getSystemManager().addSystem<DynamicDirectionalLightSystem>();
	world.getSystemManager().addSystem<DynamicPointLightSystem>();
	world.getSystemManager().addSystem<DynamicSpotLightSystem>();

	world.getSystemManager().addSystem<FloorCollideSystem>();

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
		world.getSystemManager().getSystem<ParticleSphereSystem>().Update(deltaTime);
		world.getSystemManager().getSystem<BridgeRopeSystem>().Update(deltaTime);
		world.getSystemManager().getSystem<BridgeRodSystem>().Update(deltaTime);


		world.getSystemManager().getSystem<FloorCollideSystem>().Update(deltaTime);
		// Update Transform

		// Physics
		//float fixedDeltaTime = glfwGetKey(world.data.renderUtil->window->glfwWindow, GLFW_KEY_SPACE) == GLFW_PRESS ? 1 / 60.0f : 0;		
		float fixedDeltaTime = 1 / 60.0f;
		// Force Generator
		world.getSystemManager().getSystem<GravityForceSystem>().Update(fixedDeltaTime);
		world.getSystemManager().getSystem<DragForceSystem>().Update(fixedDeltaTime);
		world.getSystemManager().getSystem<FixedSpringSystem>().Update(fixedDeltaTime);
		world.getSystemManager().getSystem<PairedSpringSystem>().Update(fixedDeltaTime);


		// Force Accumulator
		world.getSystemManager().getSystem<ForceAccumulatorSystem>().Update(fixedDeltaTime);

		// collision Resolution
		world.getSystemManager().getSystem<ParticleCollisionResolvingSystem>().Update(fixedDeltaTime);
		world.getSystemManager().getSystem<PenetrationMovementResetSystem>().Update(fixedDeltaTime);

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

		input(world);

		// Update debug delta
		debugDelta = glfwGetTime() - stepTime;
		stepTime = glfwGetTime();

		world.data.renderUtil->SwapBuffers(world.data.renderUtil->window->glfwWindow);

	}

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

void MakeFireworks(ECSWorld& world)
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

void Make3Particles(ECSWorld& world)
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

void MakeABunchaSprings(ECSWorld& world)
{
	auto particle1 = world.createEntity();
	particle1.addComponent<TransformComponent>(Vector3(0, 20, -50));
	particle1.addComponent<ParticleComponent>(Vector3(0, 0, 0));
	particle1.addComponent<ForceAccumulatorComponent>();
	particle1.addComponent<GravityForceComponent>();

	auto particle2 = world.createEntity();
	particle2.addComponent<TransformComponent>(Vector3(-10, 0, -50));
	particle2.addComponent<ParticleComponent>(Vector3(0, 0, 0));
	particle2.addComponent<ForceAccumulatorComponent>();
	particle2.addComponent<GravityForceComponent>();

	auto spring1 = world.createEntity();
	spring1.addComponent<TransformComponent>(Vector3(10, 60, -50));
	spring1.addComponent<FixedSpringComponent>(20.0f, 20.0f, particle1);

	auto spring2 = world.createEntity();
	spring2.addComponent<TransformComponent>(Vector3(-10, 60, -50));
	spring2.addComponent<FixedSpringComponent>(20.0f, 15.0f, particle1);

	auto pairedSpring = world.createEntity();
	pairedSpring.addComponent<PairedSpringComponent>(20.0f, 20.0f, particle1, particle2);

}

void MakeABunchaSpheres(ECSWorld& world)
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

void CreateRopeBridgeParticleComponents(ECSEntity e)
{
	e.addComponent<ParticleComponent>();
	e.addComponent<ForceAccumulatorComponent>();
	e.addComponent<GravityForceComponent>();
	e.addComponent<PenetrationMovementComponent>();
}

void MakeRopeBridge(ECSWorld& world)
{
	// create ropes, anchors and rods for the first square
	auto eAnchor1 = world.createEntity();
	eAnchor1.addComponent<TransformComponent>(Vector3(3, 10, 5));

	auto e1 = world.createEntity();
	e1.addComponent<TransformComponent>(Vector3(0, 3, 5));
	CreateRopeBridgeParticleComponents(e1);

	auto eAnchor2 = world.createEntity();
	eAnchor2.addComponent<TransformComponent>(Vector3(3, 10, -5));

	auto e2 = world.createEntity();
	e2.addComponent<TransformComponent>(Vector3(0, 2, -5));
	CreateRopeBridgeParticleComponents(e2);

	//rod connecting rope 1 & 2
	auto rod1 = world.createEntity();
	rod1.addComponent<BridgeRodComponent>(e1, e2, 10);

	auto rope1 = world.createEntity();
	rope1.addComponent<BridgeRopeComponent>(eAnchor1, e1, 20, 1);  

	auto rope2 = world.createEntity();
	rope2.addComponent<BridgeRopeComponent>(eAnchor2, e2, 20, 1);

	// create ropes, anchors and rods for the second square
	auto eAnchor3 = world.createEntity();
	eAnchor3.addComponent<TransformComponent>(Vector3(3 + 10, 10, 5));

	auto e3 = world.createEntity();
	e3.addComponent<TransformComponent>(Vector3(0 + 10, -2, 5));
	CreateRopeBridgeParticleComponents(e3);

	auto eAnchor4 = world.createEntity();
	eAnchor4.addComponent<TransformComponent>(Vector3(3 + 10, 10, -5));

	auto e4 = world.createEntity();
	e4.addComponent<TransformComponent>(Vector3(0 + 10, 0, -5));
	CreateRopeBridgeParticleComponents(e4);

	//rod connecting rope 3 & 4
	auto rod2 = world.createEntity();
	rod2.addComponent<BridgeRodComponent>(e3, e4, 10);

	auto rope3 = world.createEntity();
	rope3.addComponent<BridgeRopeComponent>(eAnchor3, e3, 20, 1);

	auto rope4 = world.createEntity();
	rope4.addComponent<BridgeRopeComponent>(eAnchor4, e4, 20, 1);

	// create ropes, anchors and rods for the third square
	auto eAnchor5 = world.createEntity();
	eAnchor5.addComponent<TransformComponent>(Vector3(3 - 10, 10, 5));

	auto e5 = world.createEntity();
	e5.addComponent<TransformComponent>(Vector3(0 - 10, 1, 5));
	CreateRopeBridgeParticleComponents(e5);

	auto eAnchor6 = world.createEntity();
	eAnchor6.addComponent<TransformComponent>(Vector3(3 - 10, 10, -5));

	auto e6 = world.createEntity();
	e6.addComponent<TransformComponent>(Vector3(0 - 10, -1, -5));
	CreateRopeBridgeParticleComponents(e6);

	//rod connecting rope 5 & 6
	auto rod3 = world.createEntity();
	rod3.addComponent<BridgeRodComponent>(e5, e6, 10);

	auto rope5 = world.createEntity();
	rope5.addComponent<BridgeRopeComponent>(eAnchor5, e5, 20, 1);

	auto rope6 = world.createEntity();
	rope6.addComponent<BridgeRopeComponent>(eAnchor6, e6, 20, 1);

	// create ropes, anchors and rods for the fourth square
	auto eAnchor7 = world.createEntity();
	eAnchor7.addComponent<TransformComponent>(Vector3(3 - 20, 10, 5));

	auto e7 = world.createEntity();
	e7.addComponent<TransformComponent>(Vector3(0 - 20, 1, 5));
	CreateRopeBridgeParticleComponents(e7);

	auto eAnchor8 = world.createEntity();
	eAnchor8.addComponent<TransformComponent>(Vector3(3 - 20, 10, -5));

	auto e8 = world.createEntity();
	e8.addComponent<TransformComponent>(Vector3(0 - 20, -1, -5));
	CreateRopeBridgeParticleComponents(e8);

	//rod connecting rope 7 & 8
	auto rod4 = world.createEntity();
	rod4.addComponent<BridgeRodComponent>(e7, e8, 10);

	auto rope7 = world.createEntity();
	rope7.addComponent<BridgeRopeComponent>(eAnchor7, e7, 20, 1);

	auto rope8 = world.createEntity();
	rope8.addComponent<BridgeRopeComponent>(eAnchor8, e8, 20, 1);

	// create ropes, anchors and rods for the fifth square
	auto eAnchor9 = world.createEntity();
	eAnchor9.addComponent<TransformComponent>(Vector3(3 - 30, 10, 5));

	auto e9 = world.createEntity();
	e9.addComponent<TransformComponent>(Vector3(0 - 30, 1, 5));
	CreateRopeBridgeParticleComponents(e9);

	auto eAnchor10 = world.createEntity();
	eAnchor10.addComponent<TransformComponent>(Vector3(3 - 30, 10, -5));

	auto e10 = world.createEntity();
	e10.addComponent<TransformComponent>(Vector3(0 - 30, -1, -5));
	CreateRopeBridgeParticleComponents(e10);

	//rod connecting rope 9 & 10
	auto rod5 = world.createEntity();
	rod5.addComponent<BridgeRodComponent>(e9, e10, 10);

	auto rope9 = world.createEntity();
	rope9.addComponent<BridgeRopeComponent>(eAnchor9, e9, 20, 1);

	auto rope10 = world.createEntity();
	rope10.addComponent<BridgeRopeComponent>(eAnchor10, e10, 20, 1);

	auto eAnchor11 = world.createEntity();
	eAnchor11.addComponent<TransformComponent>(Vector3(3 - 40, 10, 5));

	auto e11 = world.createEntity();
	e11.addComponent<TransformComponent>(Vector3(0 - 40, 1, 5));
	CreateRopeBridgeParticleComponents(e11);

	auto eAnchor12 = world.createEntity();
	eAnchor12.addComponent<TransformComponent>(Vector3(3 - 40, 10, -5));

	auto e12 = world.createEntity();
	e12.addComponent<TransformComponent>(Vector3(0 - 40, -1, -5));
	CreateRopeBridgeParticleComponents(e12);

	//rod connecting rope 11 & 12
	auto rod6 = world.createEntity();
	rod6.addComponent<BridgeRodComponent>(e11, e12, 10);

	auto rope11 = world.createEntity();
	rope11.addComponent<BridgeRopeComponent>(eAnchor11, e11, 20, 1);

	auto rope12 = world.createEntity();
	rope12.addComponent<BridgeRopeComponent>(eAnchor12, e12, 20, 1);

	//Outlining rods
	//First Square 
	auto rod7 = world.createEntity();
	rod7.addComponent<BridgeRodComponent>(e1, e3, 10);
	auto rod8 = world.createEntity();
	rod8.addComponent<BridgeRodComponent>(e2, e4, 10);

	//Second Square 
	auto rod9 = world.createEntity();
	rod9.addComponent<BridgeRodComponent>(e5, e1, 10);
	auto rod10 = world.createEntity();
	rod10.addComponent<BridgeRodComponent>(e6, e2, 10);

	//Third Square 
	auto rod17 = world.createEntity();
	rod17.addComponent<BridgeRodComponent>(e5, e7, 10);
	auto rod18 = world.createEntity();
	rod18.addComponent<BridgeRodComponent>(e8, e6, 10);

	//Fourth Square 
	auto rod19 = world.createEntity();
	rod19.addComponent<BridgeRodComponent>(e9, e7, 10);
	auto rod20 = world.createEntity();
	rod20.addComponent<BridgeRodComponent>(e10, e8, 10);

	//Fifth Square 
	auto rod11 = world.createEntity();
	rod11.addComponent<BridgeRodComponent>(e11, e9, 10);
	auto rod12 = world.createEntity();
	rod12.addComponent<BridgeRodComponent>(e12, e10, 10);

	//Crossing Rods
	//First Square 
	auto rod13 = world.createEntity();
	rod13.addComponent<BridgeRodComponent>(e1, e4, 10 * pow(2.0f, 0.5f));
	auto rod14 = world.createEntity();
	rod14.addComponent<BridgeRodComponent>(e2, e3, 10 * pow(2.0f, 0.5f));

	//Second Square 
	auto rod15 = world.createEntity();
	rod15.addComponent<BridgeRodComponent>(e6, e1, 10 * pow(2.0f, 0.5f));
	auto rod16 = world.createEntity();
	rod16.addComponent<BridgeRodComponent>(e5, e2, 10 * pow(2.0f, 0.5f));

	//Third Square 
	auto rod21 = world.createEntity();
	rod21.addComponent<BridgeRodComponent>(e7, e6, 10 * pow(2.0f, 0.5f));
	auto rod22 = world.createEntity();
	rod22.addComponent<BridgeRodComponent>(e5, e8, 10 * pow(2.0f, 0.5f));

	//Fourth Square 
	auto rod23 = world.createEntity();
	rod23.addComponent<BridgeRodComponent>(e9, e8, 10 * pow(2.0f, 0.5f));
	auto rod24 = world.createEntity();
	rod24.addComponent<BridgeRodComponent>(e10, e7, 10 * pow(2.0f, 0.5f));

	//Fifth Square 
	auto rod25 = world.createEntity();
	rod25.addComponent<BridgeRodComponent>(e11, e10, 10 * pow(2.0f, 0.5f));
	auto rod26 = world.createEntity();
	rod26.addComponent<BridgeRodComponent>(e12, e9, 10 * pow(2.0f, 0.5f));

	//Triangle Floors with colliders
	//First Square third
	auto triFloor1 = world.createEntity();
	triFloor1.addComponent<FloorCollideComponent>(e4, e3, e2);
	triFloor1.addComponent<ParticleComponent>(Vector3(0, 0, 0));

	auto triFloor1_2 = world.createEntity();
	triFloor1_2.addComponent<FloorCollideComponent>(e2, e3, e1);
	triFloor1_2.addComponent<ParticleComponent>(Vector3(0, 0, 0));



	//Second Square first
	auto triFloor2 = world.createEntity();
	triFloor2.addComponent<FloorCollideComponent>(e5, e6, e2);
	triFloor2.addComponent<ParticleComponent>(Vector3(0, 0, 0));

	auto triFloor2_2 = world.createEntity();
	triFloor2_2.addComponent<FloorCollideComponent>(e1, e5, e2);
	triFloor2_2.addComponent<ParticleComponent>(Vector3(0, 0, 0));


	//Third Square second
	auto triFloor3 = world.createEntity();
	triFloor3.addComponent<FloorCollideComponent>(e5, e7, e8);
	triFloor3.addComponent<ParticleComponent>(Vector3(0, 0, 0));

	auto triFloor3_2 = world.createEntity();
	triFloor3_2.addComponent<FloorCollideComponent>(e6, e5, e8);
	triFloor3_2.addComponent<ParticleComponent>(Vector3(0, 0, 0));
	

	//Fourth Square 
	auto triFloor4 = world.createEntity();
	triFloor4.addComponent<FloorCollideComponent>(e8, e7, e9);
	triFloor4.addComponent<ParticleComponent>(Vector3(0, 0, 0));

	auto triFloor4_2 = world.createEntity();
	triFloor4_2.addComponent<FloorCollideComponent>(e10, e8, e9);
	triFloor4_2.addComponent<ParticleComponent>(Vector3(0, 0, 0));


	//Fifth Square 
	auto triFloor5 = world.createEntity();
	triFloor5.addComponent<FloorCollideComponent>(e11, e12, e10);
	triFloor5.addComponent<ParticleComponent>(Vector3(0, 0, 0));

	auto triFloor5_2 = world.createEntity();
	triFloor5_2.addComponent<FloorCollideComponent>(e10, e9, e11);
	triFloor5_2.addComponent<ParticleComponent>(Vector3(0, 0, 0));

}


void input(ECSWorld& world)
{
	GLFWwindow* window = world.data.renderUtil->window->glfwWindow;

	
	if (spawnBall == false)
	{
		auto testBall1 = world.createEntity();

		testBall1.addComponent<ParticleSphereComponent>(1.0f);
		testBall1.addComponent<TransformComponent>(Vector3(RANDOM_FLOAT(-15, 10), 10, -1));
		testBall1.addComponent<GravityForceComponent>(1.0f);
		testBall1.addComponent<ForceAccumulatorComponent>();
		testBall1.addComponent<ParticleComponent>();
		spawnBall = true;
		testBall1.tag(tag);
	}

	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{

		pressed = true;
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_RELEASE && pressed)
	{
		
		world.getEntity(tag).kill();


		testBalls++;
		tag = to_string(testBalls);


		auto testBall1 = world.createEntity();
		testBall1.tag(tag);
		testBall1.addComponent<ParticleSphereComponent>(1.0f);
		testBall1.addComponent<TransformComponent>(Vector3(RANDOM_FLOAT(-40, 10), RANDOM_FLOAT(0, 10), -1));
		testBall1.addComponent<GravityForceComponent>(1.0f);
		testBall1.addComponent<ForceAccumulatorComponent>();
		testBall1.addComponent<ParticleComponent>();

		pressed = false;
	}
}

void MakeABunchaCablesAndRods(ECSWorld& world)
{
	auto ePivot = world.createEntity();
	ePivot.addComponent<TransformComponent>(Vector3(3, 10, 0));

	auto e1 = world.createEntity();
	e1.addComponent<TransformComponent>(Vector3(0, 10, 0));
	e1.addComponent<ParticleComponent>();
	e1.addComponent<ForceAccumulatorComponent>();
	e1.addComponent<GravityForceComponent>();
	e1.addComponent<ParticleSphereComponent>();
	e1.addComponent<PenetrationMovementComponent>();

	auto e2 = world.createEntity();
	e2.addComponent<TransformComponent>(Vector3(5, 5, 0));
	e2.addComponent<ParticleComponent>();
	e2.addComponent<ForceAccumulatorComponent>();
	e2.addComponent<GravityForceComponent>();
	e2.addComponent<ParticleSphereComponent>();
	e2.addComponent<PenetrationMovementComponent>();

	auto e3 = world.createEntity();
	e3.addComponent<TransformComponent>(Vector3(0, 0, 0));
	e3.addComponent<ParticleComponent>();
	e3.addComponent<ForceAccumulatorComponent>();
	e3.addComponent<GravityForceComponent>();
	e3.addComponent<ParticleSphereComponent>();
	e3.addComponent<PenetrationMovementComponent>();

	auto e4 = world.createEntity();
	e4.addComponent<TransformComponent>(Vector3(-5, 5, 0));
	e4.addComponent<ParticleComponent>();
	e4.addComponent<ForceAccumulatorComponent>();
	e4.addComponent<GravityForceComponent>();
	e4.addComponent<ParticleSphereComponent>();
	e4.addComponent<PenetrationMovementComponent>();

	auto cable1 = world.createEntity();
	//cable.addComponent<CableComponent>(ePivot, e1, 5, 1);
	cable1.addComponent<PairedSpringComponent>(50, 2, ePivot, e1);

	auto cable2 = world.createEntity();
	//cable.addComponent<CableComponent>(ePivot, e1, 5, 1);
	cable2.addComponent<PairedSpringComponent>(50, 25, ePivot, e2);

	auto cable3 = world.createEntity();
	cable3.addComponent<BridgeRopeComponent>(ePivot, e3, 15, 1);
	//cable3.addComponent<PairedSpringComponent>(50, 20, ePivot, e3);

	auto rod1 = world.createEntity();
	rod1.addComponent<BridgeRodComponent>(e1, e2, 5 * pow(2, 0.5f));

	auto rod2 = world.createEntity();
	rod2.addComponent<BridgeRodComponent>(e2, e3, 5 * pow(2, 0.5f));

	auto rod3 = world.createEntity();
	rod3.addComponent<BridgeRodComponent>(e3, e4, 5 * pow(2, 0.5f));

	auto rod4 = world.createEntity();
	rod4.addComponent<BridgeRodComponent>(e4, e1, 5 * pow(2, 0.5f));

	auto rod5 = world.createEntity();
	rod5.addComponent<BridgeRodComponent>(e1, e3, 10);

	auto rod6 = world.createEntity();
	rod6.addComponent<BridgeRodComponent>(e2, e4, 10);

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