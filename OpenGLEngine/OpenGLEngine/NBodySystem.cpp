#include "NBodySystem.h"
#include "TransformComponent.h"
#include "ForceAccumulatorComponent.h"

namespace Reality
{
	NBodySystem::NBodySystem()
	{
		requireComponent<NBodyComponent>();
	}

	void NBodySystem::Update(float deltaTime)
	{
		for (auto e1 : getEntities())
		{
			if (e1.hasComponent<TransformComponent>())
			{
				auto& transform1 = e1.getComponent<TransformComponent>();
				auto& nBody1 = e1.getComponent<NBodyComponent>();
		
				for (auto e2 : getEntities())
				{
					if (e1 != e2)
					{
						if (e2.hasComponent<TransformComponent>())
						{
							auto& transform2 = e2.getComponent<TransformComponent>();
							auto& nBody2 = e2.getComponent<NBodyComponent>();
		
							Vector3 relativePosition = transform1.position - transform2.position;
		
							float length = glm::length(relativePosition);
		
							float forceN;
		
							forceN = nGravity * ((nBody1.mass * nBody2.mass) / length);
		
		
							if (e2.hasComponent<ForceAccumulatorComponent>())
							{
								e2.getComponent<ForceAccumulatorComponent>().AddForce(relativePosition * forceN);
							}
		
							if (DEBUG_LOG_LEVEL > 0)
							{
								getWorld().data.renderUtil->DrawSphere(transform1.position, nBody1.mass > 100 ? 5 : nBody1.mass / 5, Color());
							}
						}
					}
				}
			}
		}
		//if (getEntities().size() > 1)
		//{
		//	for (int i = 0; i < getEntities().size() - 1; i++)
		//	{
		//		if (getEntities()[i].hasComponent<TransformComponent>())
		//		{
		//			auto& transform1 = getEntities()[i].getComponent<TransformComponent>();
		//			auto& nBody1 = getEntities()[i].getComponent<NBodyComponent>();
		//
		//			for (int j = i + 1; j < getEntities().size(); j++)
		//			{
		//				if (getEntities()[j].hasComponent<TransformComponent>())
		//				{
		//					auto& transform2 = getEntities()[j].getComponent<TransformComponent>();
		//					auto& nBody2 = getEntities()[j].getComponent<NBodyComponent>();
		//
		//					Vector3 relativePosition = transform1.position - transform2.position;
		//
		//					float length = glm::length(relativePosition);
		//
		//					float forceN;
		//
		//					forceN = nGravity * ((nBody1.mass * nBody2.mass) / length);
		//
		//					if (getEntities()[j].hasComponent<ForceAccumulatorComponent>())
		//					{
		//						getEntities()[j].getComponent<ForceAccumulatorComponent>().AddForce(relativePosition * forceN);
		//					}
		//
		//					if (DEBUG_LOG_LEVEL > 0)
		//					{
		//						getWorld().data.renderUtil->DrawSphere(transform1.position, nBody1.mass > 100 ? 5 : nBody1.mass / 20, Color::Red);
		//					}
		//				}
		//
		//			}
		//		}
		//	}
		//}
	}
}
