#include "RenderComponent.h"
#include "GameObject.h"
#include "Texture2D.h"
#include "Renderer.h"

void dae::RenderComponent::Initialize(std::shared_ptr<Texture2D> texture)
{
	m_needsRender = true;
	m_texture = texture;
}

void dae::RenderComponent::Render() const
{
	auto transform = m_Parent.lock()->GetComponent<TransformComponent>();

	auto &renderer = Renderer::GetInstance();

	renderer.SetRenderPos(transform->GetPosition());
	renderer.RenderTexture(*m_texture);

}

void dae::RenderComponent::SetParent(std::weak_ptr<GameObject> parent)
{
	m_Parent = parent;
}
