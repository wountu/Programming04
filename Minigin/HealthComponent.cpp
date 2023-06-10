#include "HealthComponent.h"
#include "GameObject.h"

dae::HealthComponent::~HealthComponent()
{
	for (auto& observer : m_pObservers)
		delete observer;

	m_pObservers.clear();
}

void dae::HealthComponent::Initialize(int health, glm::vec2 respawnPos, std::shared_ptr<GameObject> parent)
{
	m_Health = health;
	m_Parent = parent.get();
	m_RespawnPos = respawnPos;
}

void dae::HealthComponent::Update()
{
	for (const auto& observer : m_pObservers)
		observer->Update();
}

void dae::HealthComponent::Render() const
{
	for (const auto& observer : m_pObservers)
		observer->Render();
}

void dae::HealthComponent::AddObserver(Observer* observer)
{
	m_pObservers.emplace_back(observer);
}

void dae::HealthComponent::RemoveObserver(std::unique_ptr<Observer> observer)
{
	m_pObservers.erase(std::remove(m_pObservers.begin(), m_pObservers.end(), observer.get()), m_pObservers.end());
}

void dae::HealthComponent::Notify(Observer::Event event)
{
	for (const auto& observer : m_pObservers)
	{
		observer->HandleEvent(m_Parent, event);
	}
}

int dae::HealthComponent::GetHealth() const
{
	return m_Health;
}

void dae::HealthComponent::LoseHealth()
{
	Notify(dae::Observer::Health_Lost);
	--m_Health;

	//std::cout << "Got hit\n";

	m_Parent->GetComponent<TransformComponent>()->ChangeLocalPosition(m_RespawnPos);
}
