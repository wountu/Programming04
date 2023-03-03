#include "RenderComponent.h"
#include "GameObject.h"
#include "Texture2D.h"
#include "Renderer.h"

void dae::RenderComponent::Initialize(std::shared_ptr<Texture2D> texture, std::shared_ptr<GameObject> parent)
{
	m_needsRender = true;
	m_texture = texture;
	m_Parent = parent;
	m_transform = m_Parent->GetComponent<TransformComponent>();
}

void dae::RenderComponent::Render() const
{
	auto &renderer = Renderer::GetInstance();

	renderer.SetRenderPos(m_transform->GetPosition());
	renderer.RenderTexture(*m_texture);
}
