#include "BuoyancySystem.h"
#include "ForceAndTorqueAccumulatorComponent.h"
#include "RigidbodyComponent.h"
#include "ThrusterComponent.h"
#include "LifeTimeComponent.h"

namespace Reality
{
	BuoyancySystem::BuoyancySystem()
	{
		requireComponent<BuoyancyComponent>();
		requireComponent<TransformComponentV2>();
	}

	void BuoyancySystem::Update(float deltaTime)
	{

		for (auto e : getEntities())
		{
			auto& buoyancy = e.getComponent<BuoyancyComponent>();
			auto& transform = e.getComponent<TransformComponentV2>();
			auto& boatRigidbody = buoyancy.target.getComponent<RigidbodyComponent>();
			auto& boatTran = buoyancy.target.getComponent<TransformComponentV2>();
			auto& forceAcc = buoyancy.target.getComponent<ForceAndTorqueAccumulatorComponent>();

			timer += deltaTime;
			if (timer > 1000) timer = 0.0f;

			Vector3 newPosition = boatTran.LocalToWorldPosition(buoyancy.offset);
			transform.SetPosition(newPosition);
			transform.SetOrientation(boatTran.GetOrientation());

			float volume = pow(buoyancy.componentLength, 3);
			float depth = transform.GetPosition().y - buoyancy.componentLength / 2;
			Vector3 tForce = Vector3(0);

			for (int key : buoyancy.HorizontalKeys) {
				if (glfwGetKey(getWorld().data.renderUtil->window->glfwWindow, key) == GLFW_PRESS) {
					if (buoyancy.currentDensity > buoyancy.liquidDensity)
						buoyancy.currentDensity -= buoyancy.liquidDensity * 0.01;
					else
						buoyancy.currentDensity = buoyancy.liquidDensity;
				}
				else {
					if (buoyancy.currentDensity < buoyancy.liquidDensity)
						buoyancy.currentDensity += buoyancy.liquidDensity * 0.01;
					else
						buoyancy.currentDensity = buoyancy.liquidDensity;
				}
			}

			if (depth <= buoyancy.waterHeight - buoyancy.componentLength && depth + buoyancy.componentLength > -cubeSideLength + buoyancy.waterHeight) {
				if (buoyancy.offset.z > 0) {
					float densityOffset = 0.2 * sin(timer) + 1;
					tForce.y += deltaTime * buoyancy.currentDensity * densityOffset * volume;
				}
				else {
					tForce.y += deltaTime * buoyancy.currentDensity * volume;
				}
				buoyancy.netForce = buoyancy.netForce + (deltaTime * 10 * (tForce - buoyancy.netForce));
			}

			else if (depth + buoyancy.componentLength > -cubeSideLength + buoyancy.waterHeight) {
				if (buoyancy.offset.z > 0) {
					float densityOffset = 0.2 * sin(timer) + 1;
					tForce.y += deltaTime * buoyancy.currentDensity * densityOffset * (buoyancy.waterHeight - depth) * buoyancy.componentLength * buoyancy.componentLength;
				}
				else {
					tForce.y += deltaTime * buoyancy.currentDensity * (buoyancy.waterHeight - depth) * buoyancy.componentLength * buoyancy.componentLength;
				}
				buoyancy.netForce = buoyancy.netForce + (deltaTime * 10 * (tForce - buoyancy.netForce));
			}

			forceAcc.AddForceAtPoint(tForce, transform.GetPosition(), boatTran.GetPosition());

			getWorld().data.renderUtil->DrawCube(Vector3(0.0f, buoyancy.waterHeight - 20, 0.0f), Vector3(cubeSideLength, 20, cubeSideLength), Vector3(0), Color::Blue);
		}

	}
}
