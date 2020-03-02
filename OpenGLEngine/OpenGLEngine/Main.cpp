/*--------------------------------------------------------
Team Spheres: Brian Viveiros and Emmanuel Nofuente-Loblack
----------------------------------------------------------*/
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
void ForceGenerator(Reality::ECSWorld& world, float fixedDeltaTime);
void GameLogic(Reality::ECSWorld& world, float deltaTime);
void RenderUpdate(Reality::ECSWorld& world, float deltaTime, float& elapsedDeltaTime, float time, float& logicDelta, float& stepTime);
void LoadModels(ECSWorld& world);
void CreateCablesAndRods(ECSWorld& world);

void Entity_Creation(Reality::ECSWorld& world, Mix::Entity& ePivot, Mix::Entity& e1, Mix::Entity& e2, Mix::Entity& e3, Mix::Entity& e4);

void MakeARopeBridge(ECSWorld& world);
void BridgeColsSphere(Reality::ECSWorld& world);
void InputBridge(ECSWorld& world);

bool bPressSpace = false;
bool bPressUp = false;
bool bPressDown = false;
ECSEntity lastConnectedParticle = ECSEntity();
ECSEntity BridgeColSphere;

int main()
{
	ECSWorld world;

	world.data.InitRendering();

	world.data.renderUtil->camera.Position = Vector3(0, 0.0f, 50.0f);
	world.data.renderUtil->SetFOV(60);

	auto e = world.createEntity();
	e.addComponent<FPSControlComponent>();

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

	MakeARopeBridge(world);
	
	LoadShaders(world);
	bool shadersLoaded = false;
	bool modelsLoadStarted = false;

	float time = glfwGetTime();
	float stepTime = glfwGetTime();
	float deltaTime = 0;
	float elapsedDeltaTime = 0;
	float logicDelta = 0;
	float debugDelta = 0;



	// game loop
	// -----------
	while (!glfwWindowShouldClose(world.data.renderUtil->window->glfwWindow))
	{
		float current = glfwGetTime();
		deltaTime = current - time;
		deltaTime = 1 / 60.0f;
		time = glfwGetTime();

		world.update();

		// OpenGl events
		glfwPollEvents();

		world.data.renderUtil->ClearDisplay(world.data.renderUtil->window->glfwWindow);

		// Load shaders
		if (!shadersLoaded)
		{
			shadersLoaded = world.data.assetLoader->ShadersLoaded();
		}
		if(shadersLoaded && !modelsLoadStarted)
		{
			LoadModels(world);
			modelsLoadStarted = true;
		}

		// View Update
		world.data.renderUtil->UpdateViewMatrix();
		
		world.getSystemManager().getSystem<InputEventSystem>().Update(deltaTime);

		InputBridge(world);

		// Update for Game Logic
		GameLogic(world, deltaTime);

		float fixedDeltaTime = 1 / 60.0f;

		ForceGenerator(world, fixedDeltaTime);

		// Force Accumulator
		world.getSystemManager().getSystem<ForceAccumulatorSystem>().Update(fixedDeltaTime);

		// Contact Resolution
		world.getSystemManager().getSystem<ParticleContactResolutionSystem>().Update(fixedDeltaTime);
		world.getSystemManager().getSystem<ResetPenetrationDeltaMoveSystem>().Update(fixedDeltaTime);

		// Integrator
		world.getSystemManager().getSystem<ParticleSystem>().Update(fixedDeltaTime);

		// Rendering Update
		RenderUpdate(world, deltaTime, elapsedDeltaTime, time, logicDelta, stepTime);

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
	}

	glfwTerminate();
	return 0;
}

void RenderUpdate(Reality::ECSWorld& world, float deltaTime, float& elapsedDeltaTime, float time, float& logicDelta, float& stepTime)
{
	world.data.renderUtil->DrawCube(Vector3(0, 0, 0), Vector3(0, 0, 0));
	world.getSystemManager().getSystem<DynamicDirectionalLightSystem>().Update(deltaTime);
	world.getSystemManager().getSystem<DynamicPointLightSystem>().Update(deltaTime);
	world.getSystemManager().getSystem<DynamicSpotLightSystem>().Update(deltaTime);
	world.getSystemManager().getSystem<RenderingSystem>().Update(deltaTime);

	elapsedDeltaTime = glfwGetTime() - time;
	logicDelta = elapsedDeltaTime - world.data.renderUtil->GetRenderDelta();
	stepTime = glfwGetTime();
}

void GameLogic(Reality::ECSWorld& world, float deltaTime)
{
	world.getSystemManager().getSystem<FPSControlSystem>().Update(deltaTime);
	world.getSystemManager().getSystem<RotateSystem>().Update(deltaTime);
	world.getSystemManager().getSystem<FireworksSystem>().Update(deltaTime);
	world.getSystemManager().getSystem<ParticleSphereSystem>().Update(deltaTime);
	world.getSystemManager().getSystem<CableSystem>().Update(deltaTime);
	world.getSystemManager().getSystem<RodSystem>().Update(deltaTime);
	world.getSystemManager().getSystem<TriangleOfBridgeSystem>().Update(deltaTime);
}

void ForceGenerator(Reality::ECSWorld& world, float fixedDeltaTime)
{
	// Force Generator
	world.getSystemManager().getSystem<GravityForceSystem>().Update(fixedDeltaTime);
	world.getSystemManager().getSystem<DragForceSystem>().Update(fixedDeltaTime);
	world.getSystemManager().getSystem<FixedSpringSystem>().Update(fixedDeltaTime);
	world.getSystemManager().getSystem<PairedSpringSystem>().Update(fixedDeltaTime);
	world.getSystemManager().getSystem<BungeeChordSystem>().Update(fixedDeltaTime);
	world.getSystemManager().getSystem<PairedBungeeChordSystem>().Update(fixedDeltaTime);
	world.getSystemManager().getSystem<BuoyancySystem>().Update(fixedDeltaTime);
	world.getSystemManager().getSystem<NBodySystem>().Update(fixedDeltaTime);
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

void CreateParticleArchetype(ECSEntity e)
{
	e.addComponent<ParticleComponent>();
	e.addComponent<ForceAccumulatorComponent>();
	e.addComponent<GravityForceComponent>();
	e.addComponent<PenetrationDeltaMoveComponent>();
}

void MakeARopeBridge(ECSWorld & world)
{
	BridgeColsSphere(world);

	//Cable 1
	auto ePivot1 = world.createEntity();
	ePivot1.addComponent<TransformComponent>(Vector3(3, 10, 5));

	auto e1 = world.createEntity();
	e1.addComponent<TransformComponent>(Vector3(0, 3, 5));
	CreateParticleArchetype(e1);

	auto cable1 = world.createEntity();
	cable1.addComponent<CableComponent>(ePivot1, e1, 20, 1);


	//Cable 2
	auto ePivot2 = world.createEntity();
	ePivot2.addComponent<TransformComponent>(Vector3(3, 10, -5));

	auto e2 = world.createEntity();
	e2.addComponent<TransformComponent>(Vector3(0, 2, -5));
	CreateParticleArchetype(e2);

	auto cable2 = world.createEntity();
	cable2.addComponent<CableComponent>(ePivot2, e2, 20, 1);

	//Connecting Cable 1 and 2
	auto rod1 = world.createEntity();
	rod1.addComponent<RodComponent>(e1, e2, 10);


	//Cable 3
	auto ePivot3 = world.createEntity();
	ePivot3.addComponent<TransformComponent>(Vector3(3 + 10, 10, 5));

	auto e3 = world.createEntity();
	e3.addComponent<TransformComponent>(Vector3(0 + 10, -2, 5));
	CreateParticleArchetype(e3);

	auto cable3 = world.createEntity();
	cable3.addComponent<CableComponent>(ePivot3, e3, 22, 1);


	//Cable 4
	auto ePivot4 = world.createEntity();
	ePivot4.addComponent<TransformComponent>(Vector3(3 + 10, 10, -5));

	auto e4 = world.createEntity();
	e4.addComponent<TransformComponent>(Vector3(0 + 10, 0, -5));
	CreateParticleArchetype(e4);

	auto cable4 = world.createEntity();
	cable4.addComponent<CableComponent>(ePivot4, e4, 22, 1);

	//Connecting Cable 3 and 4
	auto rod2 = world.createEntity();
	rod2.addComponent<RodComponent>(e3, e4, 10);	


	//Connecting Cable 1 and 3
	auto rod3 = world.createEntity();
	rod3.addComponent<RodComponent>(e1, e3, 10);

	//Connecting Cable 2 and 4
	auto rod4 = world.createEntity();
	rod4.addComponent<RodComponent>(e2, e4, 10);

	//Connecting Cable 1 and 4
	auto rod5 = world.createEntity();
	rod5.addComponent<RodComponent>(e1, e4, 10 * pow(2.0f, 0.5f));

	//Connecting Cable 2 and 3
	auto rod6 = world.createEntity();
	rod6.addComponent<RodComponent>(e2, e3, 10 * pow(2.0f, 0.5f));

	//Traingle 1
	auto tri1 = world.createEntity();
	tri1.addComponent<TriangleOfBridgeComponent>(e2, e1, e4);

	//Traingle 2
	auto tri2 = world.createEntity();
	tri2.addComponent<TriangleOfBridgeComponent>(e3, e4, e1);


	//Cable 5
	auto ePivot5 = world.createEntity();
	ePivot5.addComponent<TransformComponent>(Vector3(3 - 10, 10, 5));

	auto e5 = world.createEntity();
	e5.addComponent<TransformComponent>(Vector3(0 - 10, 1, 5));
	CreateParticleArchetype(e5);

	auto cable5 = world.createEntity();
	cable5.addComponent<CableComponent>(ePivot5, e5, 18, 1);

	//Cable 6
	auto ePivot6 = world.createEntity();
	ePivot6.addComponent<TransformComponent>(Vector3(3 - 10, 10, -5));

	auto e6 = world.createEntity();
	e6.addComponent<TransformComponent>(Vector3(0 - 10, -1, -5));
	CreateParticleArchetype(e6);

	auto cable6 = world.createEntity();
	cable6.addComponent<CableComponent>(ePivot6, e6, 18, 1);

	//Connecting Cable 5 and 6
	auto rod7 = world.createEntity();
	rod7.addComponent<RodComponent>(e5, e6, 10);


	//Connecting Cable 1 and 5
	auto rod8 = world.createEntity();
	rod8.addComponent<RodComponent>(e5, e1, 10);
	//Connecting Cable 2 and 6
	auto rod9 = world.createEntity();
	rod9.addComponent<RodComponent>(e6, e2, 10);
	//Connecting Cable 1 and 6
	auto rod10 = world.createEntity();
	rod10.addComponent<RodComponent>(e6, e1, 10 * pow(2.0f, 0.5f));
	//Connecting Cable 2 and 5
	auto rod11 = world.createEntity();
	rod11.addComponent<RodComponent>(e5, e2, 10 * pow(2.0f, 0.5f));

	//Triangle 3
	auto tri3 = world.createEntity();
	tri3.addComponent<TriangleOfBridgeComponent>(e6, e5, e2);

	//Triangle 4
	auto tri4 = world.createEntity();
	tri4.addComponent<TriangleOfBridgeComponent>(e1, e2, e5);


	//Cable 7
	auto ePivot7 = world.createEntity();
	ePivot7.addComponent<TransformComponent>(Vector3(3 + 20, 10, 5));

	auto e7 = world.createEntity();
	e7.addComponent<TransformComponent>(Vector3(0 + 20, 1, 5));
	CreateParticleArchetype(e7);

	auto cable7 = world.createEntity();
	cable7.addComponent<CableComponent>(ePivot7, e7, 22, 1);

	//Cable 8
	auto ePivot8 = world.createEntity();
	ePivot8.addComponent<TransformComponent>(Vector3(3 + 20, 10, -5));

	auto e8 = world.createEntity();
	e8.addComponent<TransformComponent>(Vector3(0 + 20, -1, -5));
	CreateParticleArchetype(e8);

	auto cable8 = world.createEntity();
	cable8.addComponent<CableComponent>(ePivot8, e8, 22, 1);

	//Connecting Cable 7 and 8
	auto rod12 = world.createEntity();
	rod12.addComponent<RodComponent>(e7, e8, 10);


	//Connecting Cable 3 and 7
	auto rod13 = world.createEntity();
	rod13.addComponent<RodComponent>(e3, e7, 10);
	//Connecting Cable 4 and 8
	auto rod14 = world.createEntity();
	rod14.addComponent<RodComponent>(e4, e8, 10);
	//Connecting Cable 3 and 8
	auto rod15 = world.createEntity();
	rod15.addComponent<RodComponent>(e3, e8, 10 * pow(2.0f, 0.5f));
	//Connecting Cable 4 and 7
	auto rod16 = world.createEntity();
	rod16.addComponent<RodComponent>(e4, e7, 10 * pow(2.0f, 0.5f));

	//Triangle 5
	auto tri5 = world.createEntity();
	tri5.addComponent<TriangleOfBridgeComponent>(e4, e3, e8);

	//Triangle 6
	auto tri6 = world.createEntity();
	tri6.addComponent<TriangleOfBridgeComponent>(e7, e8, e3);


	//Cable 9
	auto ePivot9 = world.createEntity();
	ePivot9.addComponent<TransformComponent>(Vector3(3 + 30, 10, 5));

	auto e9 = world.createEntity();
	e9.addComponent<TransformComponent>(Vector3(0 + 30, 1, 5));
	CreateParticleArchetype(e9);

	auto cable9 = world.createEntity();
	cable9.addComponent<CableComponent>(ePivot9, e9, 20, 1);
	
	//Cable 10
	auto ePivot10 = world.createEntity();
	ePivot10.addComponent<TransformComponent>(Vector3(3 + 30, 10, -5));

	auto e10 = world.createEntity();
	e10.addComponent<TransformComponent>(Vector3(0 + 30, -1, -5));
	CreateParticleArchetype(e10);

	auto cable10 = world.createEntity();
	cable10.addComponent<CableComponent>(ePivot10, e10, 20, 1);

	//Connecting Cable 9 and 10
	auto rod17 = world.createEntity();
	rod17.addComponent<RodComponent>(e9, e10, 10);

	//Connecting Cable 7 and 9
	auto rod18 = world.createEntity();
	rod18.addComponent<RodComponent>(e7, e9, 10);
	//Connecting Cable 8 and 10
	auto rod19 = world.createEntity();
	rod19.addComponent<RodComponent>(e8, e10, 10);
	//Connecting Cable 7 and 10
	auto rod20 = world.createEntity();
	rod20.addComponent<RodComponent>(e7, e10, 10 * pow(2.0f, 0.5f));
	//Connecting Cable 8 and 9
	auto rod21 = world.createEntity();
	rod21.addComponent<RodComponent>(e8, e9, 10 * pow(2.0f, 0.5f));

	//Triangle 7
	auto tri7 = world.createEntity();
	tri7.addComponent<TriangleOfBridgeComponent>(e8, e7, e10);

	//Triangle 8
	auto tri8 = world.createEntity();
	tri8.addComponent<TriangleOfBridgeComponent>(e9, e10, e7);


	//Cable 11
	auto ePivot11 = world.createEntity();
	ePivot11.addComponent<TransformComponent>(Vector3(3 + 40, 10, 5));

	auto e11 = world.createEntity();
	e11.addComponent<TransformComponent>(Vector3(0 + 40, 1, 5));
	CreateParticleArchetype(e11);

	auto cable11 = world.createEntity();
	cable11.addComponent<CableComponent>(ePivot11, e11, 18, 1);

	//Cable 12
	auto ePivot12 = world.createEntity();
	ePivot12.addComponent<TransformComponent>(Vector3(3 + 40, 10, -5));

	auto e12 = world.createEntity();
	e12.addComponent<TransformComponent>(Vector3(0 + 40, -1, -5));
	CreateParticleArchetype(e12);

	auto cable12 = world.createEntity();
	cable12.addComponent<CableComponent>(ePivot12, e12, 18, 1);

	//Connecting Cable 11 and 12
	auto rod22 = world.createEntity();
	rod22.addComponent<RodComponent>(e11, e12, 10);


	//Connecting Cable 9 and 11
	auto rod23 = world.createEntity();
	rod23.addComponent<RodComponent>(e9, e11, 10);
	//Connecting Cable 10 and 12
	auto rod24 = world.createEntity();
	rod24.addComponent<RodComponent>(e10, e12, 10);
	//Connecting Cable 9 and 12
	auto rod25 = world.createEntity();
	rod25.addComponent<RodComponent>(e9, e12, 10 * pow(2.0f, 0.5f));
	//Connecting Cable 10 and 11
	auto rod26 = world.createEntity();
	rod26.addComponent<RodComponent>(e10, e11, 10 * pow(2.0f, 0.5f));

	//Triangle 9
	auto tri9 = world.createEntity();
	tri9.addComponent<TriangleOfBridgeComponent>(e10, e9, e12);

	//Triangle 10
	auto tri10 = world.createEntity();
	tri10.addComponent<TriangleOfBridgeComponent>(e11, e12, e9);

}

void BridgeColsSphere(Reality::ECSWorld& world)
{
	BridgeColSphere = world.createEntity();
	BridgeColSphere.addComponent<TransformComponent>(Vector3(20, 10, 0));
	BridgeColSphere.addComponent<ParticleComponent>();
	BridgeColSphere.addComponent<ForceAccumulatorComponent>(1.0f);
	BridgeColSphere.addComponent<GravityForceComponent>();
	BridgeColSphere.addComponent<PenetrationDeltaMoveComponent>();
	world.getSystemManager().getSystem<TriangleOfBridgeSystem>().SetSphere(BridgeColSphere);
}

void CreateCablesAndRods(ECSWorld & world)
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

	Entity_Creation(world, ePivot, e1, e2, e3, e4);
}

void Entity_Creation(Reality::ECSWorld& world, Mix::Entity& ePivot, Mix::Entity& e1, Mix::Entity& e2, Mix::Entity& e3, Mix::Entity& e4)
{
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
