#include "CollisionBoxComponent.h"
#include <SDL.h>

#include "Renderer.h"
#include "GameObject.h"
#include "CollisionDetector.h"


namespace dae
{
	void CollisionBoxComponent::Initialize(std::shared_ptr<GameObject> parent, CollisionBox collision, bool checkEveryFrame)
	{
		m_Parent = parent.get();

		if (!m_Parent)
			std::cout << "no parent" << "\n";

		m_CollisionBox = collision;
		m_CheckEveryFrame = checkEveryFrame;

		CollisionDetector::GetInstance().AddCollisionBox(this, m_Parent->GetTag());
	}

	void CollisionBoxComponent::Update()
	{
		m_CollisionBox._leftTop = m_Parent->GetComponent<TransformComponent>()->GetWorldPosition(); //Updating it's pos
	}

	void CollisionBoxComponent::Render() const
	{
		//Debug render

		//SDL_Rect rect;
		//rect.x = static_cast<int>(m_CollisionBox._leftTop.x);
		//rect.y = static_cast<int>(m_CollisionBox._leftTop.y);
		//rect.w = static_cast<int>(m_CollisionBox._width);
		//rect.h = static_cast<int>(m_CollisionBox._height);

		//SDL_RenderDrawRect(Renderer::GetInstance().GetSDLRenderer(), &rect);
	}

	void CollisionBoxComponent::CheckCollision()
	{
		auto collidingObject = CollisionDetector::GetInstance().BoxColliding(this, m_Parent->GetTag());
		if (collidingObject)
		{
			m_CollidingObject = collidingObject->GetParent();
		}
	}

	CollisionBox CollisionBoxComponent::GetBox() const
	{
		return m_CollisionBox;
	}

	GameObject* CollisionBoxComponent::GetOverlappingGameObject()
	{
		CheckCollision();
		return m_CollidingObject;
	}

	GameObject* CollisionBoxComponent::GetParent() const
	{
		return m_Parent;
	}

}
