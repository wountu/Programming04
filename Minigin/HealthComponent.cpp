#include "HealthComponent.h"
#include "GameObject.h"
#include "Gamemode.h"
#include "ServiceLocator.h"

void dae::HealthComponent::Initialize(int health, std::shared_ptr<GameObject> parent)
{
	m_Health = health;
	m_Parent = parent.get();

	m_SoundId = 1;
	ServiceLocator::GetSoundSystem().LoadSound(m_SoundId, "pacman_death.wav");
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

void dae::HealthComponent::RemoveObserver(Observer* observer)
{
	m_pObservers.erase(std::remove(m_pObservers.begin(), m_pObservers.end(), observer), m_pObservers.end());
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
	--m_Health;

	ServiceLocator::GetSoundSystem().Play(m_SoundId, 50);

	if (m_Health < 0)
	{
		m_Parent->SetActive(false);
		Notify(dae::Observer::Health_Died);
		//if (m_Parent->GetTag() != dae::AI)
		//	Gamemode::GetInstance().PlayerDied(m_Parent->shared_from_this());
		//else Gamemode::GetInstance().EnemyDied(m_Parent->shared_from_this());
	}
	else 
	{
		Notify(dae::Observer::Health_Lost);
	}
	 

	//std::cout << "Got hit\n";

}
