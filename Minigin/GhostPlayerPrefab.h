#pragma once
#include "BasePrefab.h"

#include "GameObject.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "Texture2D.h"
#include "PlayerComponent.h"
#include "Command.h"
#include "InputManager.h"
#include "GridGenerator.h"
#include "ScoreObserver.h"
#include "HealthObserver.h"
#include "ScoreComponent.h"

class GhostPlayerPrefab final : public BasePrefab
{
public:
	std::shared_ptr<dae::GameObject> Create(glm::vec2 pos) override
	{
		m_GhostGO = std::make_shared<dae::GameObject>();
		m_GhostGO->Initialize();
		m_GhostGO->SetTag(dae::Enemy);


		auto transform = m_GhostGO->AddComponent<dae::TransformComponent>();
		transform->Initialize(pos, 0.f, m_GhostGO);

		assert(m_Texture.get() != nullptr && "Pacman prefab needs a texture(use SetTexture)");
		auto render = m_GhostGO->AddComponent<dae::RenderComponent>();
		render->Initialize(m_Texture, m_GhostGO);

		auto collision = m_GhostGO->AddComponent<dae::CollisionBoxComponent>();
		collision->Initialize(m_GhostGO, dae::CollisionBox::CollisionBox(pos, static_cast<float>(m_Texture->GetSize().x), static_cast<float>(m_Texture->GetSize().y)), 2);
		collision->SetActive(true);

		auto health = m_GhostGO->AddComponent<dae::HealthComponent>();
		health->Initialize(m_Lives, m_GhostGO);

		auto pacmanComp = m_GhostGO->AddComponent<dae::PlayerComponent>();
		pacmanComp->Initialize(m_GhostGO, 50.f);

		auto score = m_GhostGO->AddComponent<dae::ScoreComponent>();
		score->Initialize(m_GhostGO);

		return m_GhostGO;
	}

	void SetTexture(std::shared_ptr<dae::Texture2D> texture) override
	{
		m_Texture = texture;
	}

	void SetMovementKeys(ControllerXbox::ControllerInputs left, ControllerXbox::ControllerInputs right, ControllerXbox::ControllerInputs up, ControllerXbox::ControllerInputs down, unsigned int controllerIdx)
	{
		assert(m_GhostGO && "The player GO isn't created yet, first create(Create()) the object then the SetMovementKeys");

		auto& input = dae::InputManager::GetInstance();

		auto command = input.AddCommand<dae::ChangeDir>(controllerIdx, m_GhostGO.get(), left, dae::InputManager::KeyPress::SINGLEPRESS);
		command->SetDir(glm::vec2(-1, 0));

		command = input.AddCommand<dae::ChangeDir>(controllerIdx, m_GhostGO.get(), right, dae::InputManager::KeyPress::SINGLEPRESS);
		command->SetDir(glm::vec2(1, 0));

		command = input.AddCommand<dae::ChangeDir>(controllerIdx, m_GhostGO.get(), up, dae::InputManager::KeyPress::SINGLEPRESS);
		command->SetDir(glm::vec2(0, -1));

		command = input.AddCommand<dae::ChangeDir>(controllerIdx, m_GhostGO.get(), down, dae::InputManager::KeyPress::SINGLEPRESS);
		command->SetDir(glm::vec2(0, 1));
	}

	void SetLives(int lives)
	{
		m_Lives = lives;
	}
private:
	std::shared_ptr<dae::Texture2D> m_Texture{};
	std::shared_ptr<dae::GameObject> m_GhostGO{};

	int m_Lives{ 3 };
};

