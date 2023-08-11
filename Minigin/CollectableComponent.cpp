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

	Notify(dae::Observer::Collectable_Added);
}

void dae::CollectableComponent::Update()
{
	auto overlap = m_CollisionBox->GetOverlappingGameObject();
	if (overlap != nullptr)
	{
		PickUp(overlap);
	}
}

void dae::CollectableComponent::AddObserver(std::shared_ptr<Observer> observer)
{
	m_Observers.emplace_back(observer);
}

void dae::CollectableComponent::RemoveObserver(std::shared_ptr<Observer> observer)
{
	m_Observers.erase(std::remove(m_Observers.begin(), m_Observers.end(), observer), m_Observers.end());
}

void dae::CollectableComponent::PickUp(GameObject* overlap)
{
	Notify(dae::Observer::Collectable_Removed);
	overlap->GetComponent<dae::ScoreComponent>()->AddScore(m_CollectableScore);
	m_Parent->Destroy();
}

void dae::CollectableComponent::Notify(Observer::Event event)
{
	for (const auto& observer : m_Observers)
		observer->HandleEvent(m_Parent, event);
}
