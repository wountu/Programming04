#include "AimComponent.h"
#include "GameObject.h"

void dae::AimComponent::Initialize(std::shared_ptr<GameObject> parent)
{
	m_Parent = parent.get();
}

void dae::AimComponent::Update()
{
	auto transform = m_Parent->GetComponent<TransformComponent>();
}

void dae::AimComponent::Render() const
{
}
