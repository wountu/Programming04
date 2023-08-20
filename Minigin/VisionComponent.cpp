#include "VisionComponent.h"
#include "GameObject.h"
#include "CollisionDetector.h"
#include "Renderer.h"
#include "RenderComponent.h"

#include <glm/glm.hpp>
#include <SDL.h>

namespace dae
{
	void VisionComponent::Initialize(std::shared_ptr<GameObject> parent, float visionLength)
	{
		m_Parent = parent.get();
		m_Transform = m_Parent->GetComponent<TransformComponent>();
		m_VisionLength = visionLength;

		auto texture = m_Parent->GetComponent<dae::RenderComponent>()->GetTexture();
		glm::vec2 dir{ -1,0 };
		glm::vec2 pos{ m_Transform->GetWorldPosition() };
		m_Offset.x = static_cast<float>(texture->GetSize().x / 2);
		m_Offset.y = static_cast<float>(texture->GetSize().y / 2);

		pos.x += m_Offset.x;
		pos.y += m_Offset.y;

		m_Visions.push_back(Vision{ pos, pos + dir * visionLength, dir });
		dir.x = 1;
		m_Visions.push_back(Vision{ pos, pos + dir * visionLength, dir });
		dir.x = 0;
		dir.y = 1;
		m_Visions.push_back(Vision{ pos, pos + dir * visionLength, dir });
		dir.y = -1;
		m_Visions.push_back(Vision{ pos, pos + dir * visionLength, dir });
	}

	void VisionComponent::Update()
	{
		for (auto& vision : m_Visions)
		{
			vision.startVision = m_Transform->GetWorldPosition() + m_Offset;

			glm::vec2 visionVec = vision.direction * m_VisionLength;
			vision.endVision = vision.startVision + visionVec;
		}

		//m_Direction = m_Transform->GetDirection();
		//m_StartVision = m_Transform->GetWorldPosition();

		//m_StartVision += m_Offset;
		//
		//glm::vec2 visionVec = m_Direction * m_VisionLength;
		//m_EndVision = m_StartVision + visionVec;
	}

	void VisionComponent::Render() const
	{
		for (const auto& vision : m_Visions)
		{
			SDL_RenderDrawLine(Renderer::GetInstance().GetSDLRenderer(), static_cast<int>(vision.startVision.x),
				static_cast<int>(vision.startVision.y), static_cast<int>(vision.endVision.x), static_cast<int>(vision.endVision.y));
		}
	}

	std::vector<GameObject*> VisionComponent::SeenObjects() const
	{
		auto& collisionDet = CollisionDetector::GetInstance();
		std::vector<GameObject*> objects;

		for (const auto& vision : m_Visions)
		{

			auto collisions = collisionDet.BoxesCollidingWithRay(vision.startVision, vision.endVision, vision.direction);
			
			for (const auto& collision : collisions)
			{
				objects.push_back(collision->GetParent());
			}
		}

		return objects;
	}

	std::vector<GameObject*> VisionComponent::ClosestSeenObjects() const
	{
		auto& collisionDet = CollisionDetector::GetInstance();
		std::vector<GameObject*> objects;

		for (const auto& vision : m_Visions)
		{
			float closestDist{ FLT_MAX };
			GameObject* closestObj{ nullptr };

			auto collisions = collisionDet.BoxesCollidingWithRay(vision.startVision, vision.endVision, vision.direction);

			for (const auto& collision : collisions)
			{
				if (collision->GetParent()->GetTag() == dae::Collectable || collision->GetParent()->GetTag() == dae::Enemy)
					continue;

 				float dist = glm::distance(collision->GetParent()->GetComponent<dae::TransformComponent>()->GetWorldPosition(), m_Transform->GetWorldPosition());
				if (dist < 20)
					continue;

				if (dist < closestDist)
				{
					closestDist = dist;
					closestObj = collision->GetParent();
				}
			}

			if(closestObj != nullptr)
			{
				objects.push_back(closestObj);
				if(closestObj->GetTag() == dae::Player1)
					std::cout << "Found one\n";
			}
		}

		return objects;
	}


	glm::vec2 VisionComponent::GetStartVision() const
	{
		return m_StartVision;
	}

	glm::vec2 VisionComponent::GetEndVision() const
	{
		return m_EndVision;
	}

	glm::vec2 VisionComponent::GetDirection() const
	{
		return m_Direction;
	}
}