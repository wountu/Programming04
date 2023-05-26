#include <SDL.h>

#include "Renderer.h"
#include "CollisionBoxComponent.h"
#include "GameObject.h"

void dae::CollisionBoxComponent::Initialize(std::shared_ptr<GameObject> parent, CollisionBox collision)
{
	m_Parent = parent.get();
	m_CollisionBox = collision;
}

void dae::CollisionBoxComponent::Update()
{
	m_CollisionBox._leftTop = m_Parent->GetComponent<TransformComponent>()->GetPosition();
}

void dae::CollisionBoxComponent::Render() const
{
	SDL_Rect rect;
	rect.x = static_cast<int>(m_CollisionBox._leftTop.x);
	rect.y = static_cast<int>(m_CollisionBox._leftTop.y);
	rect.w = static_cast<int>(m_CollisionBox._width);
	rect.h = static_cast<int>(m_CollisionBox._height);

	SDL_RenderDrawRect(Renderer::GetInstance().GetSDLRenderer(), &rect);
}
