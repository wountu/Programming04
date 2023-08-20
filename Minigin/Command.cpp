#include "Command.h"
#include "TransformComponent.h"
#include "TimeClass.h"
#include "Observer.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"
#include "Gamemode.h"
#include "MainmenuComponent.h"

namespace dae
{
	//Movement
	Movement::Movement(GameObject* pActor)
	{
		m_pTransform = pActor->GetComponent<TransformComponent>();
		m_Parent = pActor;
	}

	Movement::~Movement()
	{
		//delete m_pTransform;
		//m_pTransform = nullptr;
	}

	void Movement::Execute()
	{
		auto& timeClass = TimeClass::GetInstance();
		glm::vec2 newPos{ m_pTransform->GetLocalPosition() + (m_Direction * m_Speed * timeClass.GetElapsed()) };
		m_pTransform->ChangeLocalPosition(newPos);
		m_pTransform->SetDirection(m_Direction);
	}

	Score::Score(GameObject* parent)
	{
		m_Parent = parent;
	}

	void Score::Execute()
	{
		m_Parent->GetComponent<ScoreComponent>()->AddScore(100);
	}

	NextGamemode::NextGamemode(GameObject* parent)
	{
		m_Parent = parent;
	}

	void NextGamemode::Execute()
	{
		m_Parent->GetComponent<MainmenuComponent>()->GoNext();
	}

	PreviousGamemode::PreviousGamemode(GameObject* parent)
	{
		m_Parent = parent;
	}

	void PreviousGamemode::Execute()
	{
		m_Parent->GetComponent<MainmenuComponent>()->GoPrevious();
	}

	Start::Start(GameObject* parent)
	{
		m_Menu = parent->GetComponent<MainmenuComponent>().get();
	}

	void Start::Execute()
	{
		m_Menu->StartGame();
	}

	ChangeDir::ChangeDir(GameObject* parent)
	{
		m_Player = parent->GetComponent<dae::PlayerComponent>().get();
	}

	void ChangeDir::SetDir(glm::vec2 dir)
	{
		m_Dir = dir;
	}

	void ChangeDir::Execute()
	{
		m_Player->SetDirection(m_Dir);
	}

	NextLevel::NextLevel(GameObject* ) {};

	void NextLevel::SetGameMode(Gamemode* gameMode)
	{
		m_GameMode = gameMode;
	}
	
	void NextLevel::Execute()
	{
		m_GameMode->GoNextLevel();
	}

}