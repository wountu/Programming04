#include "TeleporterComponent.h"
#include "Gameobject.h"

void dae::TeleporterComponent::Initialize(std::shared_ptr<GameObject> parent)
{
	m_Parent = parent.get();
	m_Collision = m_Parent->GetComponent<CollisionBoxComponent>().get();
}

void dae::TeleporterComponent::Render() const
{

}

void dae::TeleporterComponent::Update()
{
	m_IsColliding = false;

	if (m_Collision)
	{
		auto overlap = m_Collision->GetOverlappingGameObject();
		if (overlap)
		{
			m_IsColliding = true;

			if (overlap == m_TeleportedObj)
			{
				return;
			}

			if (m_OtherTeleporter)
			{
				std::cout << "Teleport!\n";
				overlap->GetComponent<dae::TransformComponent>()->ChangeLocalPosition(m_OtherTeleporter->GetPosition());
				m_OtherTeleporter->Teleported(overlap);
			}
		}
		else
		{
			if (!m_OtherTeleporter->IsColliding())
				m_TeleportedObj = nullptr;
		}
	}
}

glm::vec2 dae::TeleporterComponent::GetPosition() const
{
	return m_Parent->GetComponent<TransformComponent>()->GetWorldPosition();
}

void dae::TeleporterComponent::LinkToOtherTeleporter(std::shared_ptr<TeleporterComponent> teleporter)
{
	m_OtherTeleporter = teleporter.get();
}

void dae::TeleporterComponent::Teleported(GameObject* object)
{
	m_TeleportedObj = object;
}

bool dae::TeleporterComponent::IsColliding() const
{
	return m_IsColliding;
}
