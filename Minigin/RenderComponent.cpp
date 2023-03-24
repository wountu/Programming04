#include "RenderComponent.h"
#include "GameObject.h"
#include "Texture2D.h"
#include "Renderer.h"

void dae::RenderComponent::Initialize(std::shared_ptr<Texture2D> texture, std::shared_ptr<GameObject> parent)
{
	m_texture = texture;
	m_pParent = parent.get();
	m_transform = m_pParent->GetComponent<TransformComponent>();
}

dae::RenderComponent::~RenderComponent()
{
//	m_pParent.reset();
}

void dae::RenderComponent::Render() const
{
	auto &renderer = Renderer::GetInstance();

	m_pParent->SetLocalPos(m_transform->GetPosition());

	renderer.SetRenderPos(m_pParent->GetWorldPos());
	renderer.RenderTexture(*m_texture);
}
