#include "RopeBridgeSystem.h"
#include "TransformComponent.h"
#include "ParticleContactComponent.h"

namespace Reality
{
	RopeBridgeSystem::RopeBridgeSystem()
	{
		requireComponent<RopeBridgeComponent>();
	}

	void RopeBridgeSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& ballTransform = e.getComponent<RopeBridgeComponent>().ball.getComponent<TransformComponent>();

			auto& object = e.getComponent<RopeBridgeComponent>();
			auto& transform = object.entity1.getComponent<TransformComponent>();
			auto& transform2 = object.entity2.getComponent<TransformComponent>();
			auto& transform3 = object.entity3.getComponent<TransformComponent>();
			auto& transform4 = object.entity4.getComponent<TransformComponent>();
			auto& transform5 = object.entity5.getComponent<TransformComponent>();
			auto& transform6 = object.entity6.getComponent<TransformComponent>();
			auto& transform7 = object.entity7.getComponent<TransformComponent>();
			auto& transform8 = object.entity8.getComponent<TransformComponent>();
			auto& transform9 = object.entity9.getComponent<TransformComponent>();
			auto& transform10 = object.entity10.getComponent<TransformComponent>();
			auto& transform11 = object.entity11.getComponent<TransformComponent>();
			auto& transform12 = object.entity12.getComponent<TransformComponent>();
			auto& transform13 = object.entity13.getComponent<TransformComponent>();
			auto& transform14 = object.entity14.getComponent<TransformComponent>();
			auto& transform15 = object.entity15.getComponent<TransformComponent>();
			auto& transform16 = object.entity16.getComponent<TransformComponent>();
			auto& transform17 = object.entity17.getComponent<TransformComponent>();
			auto& transform18 = object.entity18.getComponent<TransformComponent>();
			auto& transform19 = object.entity19.getComponent<TransformComponent>();
			auto& transform20 = object.entity20.getComponent<TransformComponent>();

			getWorld().data.renderUtil->DrawSphere(transform.position, 1, Color::Magenta);
			getWorld().data.renderUtil->DrawSphere(transform2.position, 1, Color::Magenta);
			getWorld().data.renderUtil->DrawSphere(transform3.position, 1, Color::Magenta);
			getWorld().data.renderUtil->DrawSphere(transform4.position, 1, Color::Magenta);
			getWorld().data.renderUtil->DrawSphere(transform5.position, 1, Color::Magenta);
			getWorld().data.renderUtil->DrawSphere(transform6.position, 1, Color::Magenta);
			getWorld().data.renderUtil->DrawSphere(transform7.position, 1, Color::Magenta);
			getWorld().data.renderUtil->DrawSphere(transform8.position, 1, Color::Magenta);
			getWorld().data.renderUtil->DrawSphere(transform9.position, 1, Color::Magenta);
			getWorld().data.renderUtil->DrawSphere(transform10.position, 1, Color::Magenta);
			getWorld().data.renderUtil->DrawSphere(transform11.position, 1, Color::Magenta);
			getWorld().data.renderUtil->DrawSphere(transform12.position, 1, Color::Magenta);
			getWorld().data.renderUtil->DrawSphere(transform13.position, 1, Color::Magenta);
			getWorld().data.renderUtil->DrawSphere(transform14.position, 1, Color::Magenta);
			getWorld().data.renderUtil->DrawSphere(transform15.position, 1, Color::Magenta);
			getWorld().data.renderUtil->DrawSphere(transform16.position, 1, Color::Magenta);
			getWorld().data.renderUtil->DrawSphere(transform17.position, 1, Color::Magenta);
			getWorld().data.renderUtil->DrawSphere(transform18.position, 1, Color::Magenta);
			getWorld().data.renderUtil->DrawSphere(transform19.position, 1, Color::Magenta);
			getWorld().data.renderUtil->DrawSphere(transform20.position, 1, Color::Magenta);

			getWorld().data.renderUtil->DrawLine(transform.position, transform2.position, Color::Orange);
			getWorld().data.renderUtil->DrawLine(transform3.position, transform4.position, Color::Orange);
			getWorld().data.renderUtil->DrawLine(transform5.position, transform6.position, Color::Orange);
			getWorld().data.renderUtil->DrawLine(transform7.position, transform8.position, Color::Orange);
			getWorld().data.renderUtil->DrawLine(transform9.position, transform10.position, Color::Orange);
			getWorld().data.renderUtil->DrawLine(transform11.position, transform12.position, Color::Orange);
			getWorld().data.renderUtil->DrawLine(transform13.position, transform14.position, Color::Orange);
			getWorld().data.renderUtil->DrawLine(transform15.position, transform16.position, Color::Orange);
			getWorld().data.renderUtil->DrawLine(transform17.position, transform18.position, Color::Orange);
			getWorld().data.renderUtil->DrawLine(transform19.position, transform20.position, Color::Orange);

			getWorld().data.renderUtil->DrawTriangle(transform2.position, transform4.position, transform6.position, Color::Green);
			getWorld().data.renderUtil->DrawTriangle(transform4.position, transform8.position, transform6.position, Color::Green);

			getWorld().data.renderUtil->DrawTriangle(transform6.position, transform8.position, transform10.position, Color::Green);
			getWorld().data.renderUtil->DrawTriangle(transform8.position, transform12.position, transform10.position, Color::Green);

			getWorld().data.renderUtil->DrawTriangle(transform10.position, transform12.position, transform14.position, Color::Green);
			getWorld().data.renderUtil->DrawTriangle(transform12.position, transform16.position, transform14.position, Color::Green);

			getWorld().data.renderUtil->DrawTriangle(transform14.position, transform16.position, transform18.position, Color::Green);
			getWorld().data.renderUtil->DrawTriangle(transform16.position, transform20.position, transform18.position, Color::Green);

			getWorld().data.renderUtil->DrawSphere(ballTransform.position, 2, Color::Yellow);

			ballTransform.position.y -= 0.1f;

			if (glfwGetKey(getWorld().data.renderUtil->window->glfwWindow, GLFW_KEY_E) == GLFW_PRESS)
				ballTransform.position = Vector3(10, 80, 40);
		}
	}
}
