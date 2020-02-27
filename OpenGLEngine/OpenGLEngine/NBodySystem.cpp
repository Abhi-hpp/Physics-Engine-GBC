#include "NBodySystem.h"
#include "TransformComponent.h"
#include "ForceAccumulatorComponent.h"

namespace Reality
{
	NBodySystem::NBodySystem()
	{
		requireComponent<TransformComponent>();
		requireComponent<NBodyComponent>();
	}

	void NBodySystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& forceAcc = e.getComponent<ForceAccumulatorComponent>();
			auto& transform = e.getComponent<TransformComponent>();
			auto& nBody = e.getComponent<NBodyComponent>();


			for (auto e1 : getEntities())
			{
				auto& transform1 = e1.getComponent<TransformComponent>();
				auto& nBody1 = e1.getComponent<NBodyComponent>();

				Vector3 relativePosition = transform.position - transform1.position;
				float length = glm::length(relativePosition);
				if (relativePosition != Vector3(0, 0, 0))
				{
					Vector3 force = -glm::normalize(relativePosition);
					force *= (nBody.gravitationalConstant * nBody.mass * nBody1.mass) / (length * length);
					cout << (nBody.gravitationalConstant * nBody.mass * nBody1.mass) / (length * length) << endl;
					forceAcc.AddForce(force);
				}



			}

			if (DEBUG_LOG_LEVEL > 0)
			{
				getWorld().data.renderUtil->DrawSphere(transform.position, 1.0f, Color::Cyan);
			}
		}
	}
}
