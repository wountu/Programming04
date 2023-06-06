#include "HealthComponent.h"
#include "GameObject.h"

void dae::HealthComponent::Initialize(int health, std::shared_ptr<GameObject> parent)
{
	m_Health = health;
	m_Parent = parent.get();
}

void dae::HealthComponent::Update()
{
}

void dae::HealthComponent::Render() const
{
}

int dae::HealthComponent::GetHealth() const
{
	return m_Health;
}

void dae::HealthComponent::LoseHealth(int amount)
{
	std::cout << "Player lost hp" << "\n";
	m_Health -= amount;
	m_Parent->NotifyObject(dae::Observer::Event::PLAYER_RECEIVED_DAMAGE);

	if (m_Health <= 0)
	{
		m_Parent->NotifyObject(dae::Observer::Event::PLAYER_DIED);
		std::cout << "Player died" << "\n";
	}
}
