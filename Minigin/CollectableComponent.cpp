#include "CollectableComponent.h"
#include "GameObject.h"
#include "ScoreComponent.h"

dae::CollectableComponent::~CollectableComponent()
{
}

void dae::CollectableComponent::Initialize(std::shared_ptr<GameObject> parent, int collectableScore)
{
	m_CollisionBox = parent->GetComponent<CollisionBoxComponent>().get();
	m_CollectableScore = collectableScore;
	m_Parent = parent.get();
}

void dae::CollectableComponent::Update()
{
	auto overlap = m_CollisionBox->GetOverlappingGameObject();
	if (overlap != nullptr)
	{
		overlap->GetComponent<dae::ScoreComponent>()->AddScore(m_CollectableScore);
		m_Parent->Destroy();
	}
}
