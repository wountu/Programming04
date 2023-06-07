#include "CollisionBoxComponent.h"
#include <SDL.h>

#include "Renderer.h"
#include "GameObject.h"
#include "CollisionDetector.h"


namespace dae
{
	void CollisionBoxComponent::Initialize(std::shared_ptr<GameObject> parent, dae::CollisionBox collision)
	{
		m_Parent = parent.get();
		m_CollisionBox = collision;

		CollisionDetector::GetInstance().AddCollisionBox(this);
	}

	void CollisionBoxComponent::Update()
	{
		auto collidingObject = CollisionDetector::GetInstance().BoxColliding(this);
		if (collidingObject)
		{
			m_CollidingObject = collidingObject->GetParent();
		}

		m_CollisionBox._leftTop = m_Parent->GetComponent<TransformComponent>()->GetLocalPosition(); //Updating it's pos
	}

	void CollisionBoxComponent::Render() const
	{

		SDL_Rect rect;
		rect.x = static_cast<int>(m_CollisionBox._leftTop.x);
		rect.y = static_cast<int>(m_CollisionBox._leftTop.y);
		rect.w = static_cast<int>(m_CollisionBox._width);
		rect.h = static_cast<int>(m_CollisionBox._height);

		SDL_RenderDrawRect(Renderer::GetInstance().GetSDLRenderer(), &rect);
	}

	CollisionBox CollisionBoxComponent::GetBox() const
	{
		return m_CollisionBox;
	}

	GameObject* CollisionBoxComponent::GetOverlappingGameObject() const
	{
		return m_CollidingObject;
	}

	GameObject* CollisionBoxComponent::GetParent() const
	{
		return m_Parent;
	}

}
