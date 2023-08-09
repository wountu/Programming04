#include "Command.h"
#include "TransformComponent.h"
#include "TimeClass.h"
#include "Observer.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"
#include "BulletManager.h"
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

	Shoot::Shoot(GameObject* parent)
	{
		m_Parent = parent;
	}

	void Shoot::Execute()
	{
		m_Parent->GetComponent<BulletManager>()->SpawnBullet(m_Direction);

		float angle = static_cast<float>(atan2(m_Direction.y, m_Direction.x));
		angle = glm::degrees(angle);

		m_Parent->GetComponent<TransformComponent>()->ChangeAngle(angle);
	}
	void Shoot::SetDirection(glm::vec2 dir)
	{
		m_Direction = dir;
	}

	NextGamemode::NextGamemode(GameObject* parent)
	{
		m_Parent = parent;
	}

	void NextGamemode::Execute()
	{
		m_Parent->GetComponent<MainmenuComponent>()->GoNext();
		
		//auto gameMode = Gamemode::GetInstance().GetGameMode();
		//auto text = m_Parent->GetComponent<TextObject>();
		//dae::Gamemode::GameModeEnum newGameMode{};
		//switch (gameMode)
		//{
		//case dae::Gamemode::SINGLE_PLAYER:
		//	newGameMode = dae::Gamemode::COOP;
		//	text->SetText("Coop");
		//	break;
		//case dae::Gamemode::COOP:
		//	newGameMode = dae::Gamemode::VERSUS;
		//	text->SetText("Versus");
		//	break;
		//case dae::Gamemode::VERSUS:
		//	newGameMode = dae::Gamemode::SINGLE_PLAYER;
		//	text->SetText("SinglePlayer");
		//	break;
		//}

		//Gamemode::GetInstance().SetGameMode(newGameMode);
	}

	Start::Start(GameObject* parent)
	{
		m_Parent = parent;
	}

	void Start::Execute()
	{
		Gamemode::GetInstance().StartGame();
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
}