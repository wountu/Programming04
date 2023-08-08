#include "CollisionBoxComponent.h"
#include <SDL.h>

#include "Renderer.h"
#include "GameObject.h"
#include "CollisionDetector.h"


namespace dae
{
	void CollisionBoxComponent::Initialize(std::shared_ptr<GameObject> parent, CollisionBox collision, int inset)
	{
		m_Parent = parent.get();

		m_Inset = inset;
		m_CollisionBox = collision;

		m_CollisionBox._leftTop.x += inset;
		m_CollisionBox._leftTop.y += inset;
		m_CollisionBox._width -= inset * 2;
		m_CollisionBox._height -= inset * 2;

		CollisionDetector::GetInstance().AddCollisionBox(this, m_Parent->GetTag());

		//m_Transform = m_Parent->GetComponent<TransformComponent>();
	}

	void CollisionBoxComponent::Update()
	{
		m_CollisionBox._leftTop = m_Parent->GetComponent<TransformComponent>()->GetWorldPosition(); //Updating it's pos

		m_CollisionBox._leftTop.x += m_Inset;
		m_CollisionBox._leftTop.y += m_Inset;
	}

	void CollisionBoxComponent::Render() const
	{
		//Debug render

		SDL_Rect rect;
		rect.x = static_cast<int>(m_CollisionBox._leftTop.x);
		rect.y = static_cast<int>(m_CollisionBox._leftTop.y);
		rect.w = static_cast<int>(m_CollisionBox._width);
		rect.h = static_cast<int>(m_CollisionBox._height);

		SDL_RenderDrawRect(Renderer::GetInstance().GetSDLRenderer(), &rect);
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
		m_CollidingObject = nullptr;
		CheckCollision();
		return m_CollidingObject;
	}

	GameObject* CollisionBoxComponent::GetParent() const
	{
		return m_Parent;
	}

	void CollisionBoxComponent::SetActive(bool active)
	{
		m_Active = active;
	}

	bool CollisionBoxComponent::IsActive() const
	{
		return m_Active;
	}

}
