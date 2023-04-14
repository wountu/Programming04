#include "HealthDisplayObserver.h"

#include <iostream>

dae::HealthDisplayObserver::HealthDisplayObserver(std::shared_ptr<GameObject> parent, int startHealth)
{
	m_Parent = parent.get();

	m_pTextObject = m_Parent->GetComponent<TextObject>();
	m_pTextObject->SetText("Health: " + std::to_string(startHealth));
}

void dae::HealthDisplayObserver::Notify(GameObject* actor, Event event)
{
	//Check if the event is receiving damage and if the actor that received dmg is the parent of the observer
	if (event == Event::PLAYER_RECEIVED_DAMAGE && actor == m_Parent->GetParent())
	{
		const int health = actor->GetComponent<HealthComponent>()->GetHealth();
		m_pTextObject->SetText("Health: " + std::to_string(health));
		std::cout << "Received damage!" << "\n";
	}

	if (event == Event::PLAYER_DIED)
	{
		std::cout << "Player died!" << "\n";
	}

}

void dae::HealthDisplayObserver::Update()
{
}

void dae::HealthDisplayObserver::Render() const
{

}
