#include "HealthDisplayObserver.h"

#include <iostream>

dae::HealthDisplayObserver::HealthDisplayObserver(std::shared_ptr<GameObject> parent, glm::vec2 pos)
{
	m_Parent = parent.get();
	m_Position = pos;

	m_pTextObject = m_Parent->GetComponent<TextObject>();
	m_pHealthComp = m_Parent->GetComponent<HealthComponent>();
	m_Health = m_pHealthComp->GetHealth();
}

dae::HealthDisplayObserver::~HealthDisplayObserver()
{
	//delete m_pTextObject;
	//m_pTextObject = nullptr;

}

void dae::HealthDisplayObserver::Notify(GameObject* , Event event)
{
	if (event == Event::PLAYER_RECEIVED_DAMAGE)
	{
		m_Health = m_pHealthComp->GetHealth();
		std::cout << "Received damage!" << "\n";
	}

	if (event == Event::PLAYER_DIED)
	{
		std::cout << "Player died!" << "\n";
	}

}

void dae::HealthDisplayObserver::Update()
{
	m_pTextObject->SetText("Health: " + std::to_string(m_Health));
}

void dae::HealthDisplayObserver::Render() const
{

}
