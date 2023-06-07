#include "RenderComponent.h"
#include "GameObject.h"
#include "Texture2D.h"
#include "Renderer.h"

void dae::RenderComponent::Initialize(std::shared_ptr<Texture2D> texture, std::shared_ptr<GameObject> parent)
{
	m_texture = texture;
	m_Parent = parent.get();
	m_transform = m_Parent->GetComponent<TransformComponent>();
}

dae::RenderComponent::~RenderComponent()
{

}

void dae::RenderComponent::Render() const
{
	auto &renderer = Renderer::GetInstance();

	//m_Parent->SetLocalPos(m_transform->GetPosition());

	renderer.SetRenderPos(m_transform->GetWorldPosition());
	renderer.SetRenderAngle(m_transform->GetAngle());
	renderer.RenderTexture(*m_texture);
}
