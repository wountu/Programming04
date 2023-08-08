#pragma once
#include "BasePrefab.h"

#include "GameObject.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "Texture2D.h"
#include "PlayerComponent.h"
#include "Command.h"
#include "InputManager.h"
#include "LevelGenerator.h"
#include "ScoreObserver.h"

class MainPlayerPrefab final : public BasePrefab
{
public:
	std::shared_ptr<dae::GameObject> Create(glm::vec2 pos) override
	{
		m_PlayerGO = std::make_shared<dae::GameObject>();
		m_PlayerGO->Initialize();
		m_PlayerGO->SetTag(dae::Player1);

		auto transform = m_PlayerGO->AddComponent<dae::TransformComponent>();
		transform->Initialize(pos, 0.f, m_PlayerGO);

		assert(m_Texture.get() != nullptr && "Pacman prefab needs a texture(use SetTexture)");
		auto render = m_PlayerGO->AddComponent<dae::RenderComponent>();
		render->Initialize(m_Texture, m_PlayerGO);

		auto pacmanComp = m_PlayerGO->AddComponent<dae::PlayerComponent>();
		pacmanComp->Initialize(m_PlayerGO, 50.f);

		auto collision = m_PlayerGO->AddComponent<dae::CollisionBoxComponent>();
		collision->Initialize(m_PlayerGO, dae::CollisionBox::CollisionBox(pos, static_cast<float>(m_Texture->GetSize().x), static_cast<float>(m_Texture->GetSize().y)), 0);

		auto score = m_PlayerGO->AddComponent<dae::ScoreComponent>();
		score->Initialize(m_PlayerGO);

		return m_PlayerGO;
	}

	void SetTexture(std::shared_ptr<dae::Texture2D> texture) override
	{
		m_Texture = texture;
	}

	void SetMovementKeys(SDL_Scancode left, SDL_Scancode right, SDL_Scancode up, SDL_Scancode down)
	{
		assert(m_PlayerGO && "The player GO isn't created yet, first create(Create()) the object then the SetMovementKeys");

		auto& input = dae::InputManager::GetInstance();

		auto command = input.AddCommand<dae::ChangeDir>(m_PlayerGO.get(), left, dae::InputManager::KeyPress::SINGLEPRESS);
		command->SetDir(glm::vec2(-1, 0));

		command = input.AddCommand<dae::ChangeDir>(m_PlayerGO.get(), right, dae::InputManager::KeyPress::SINGLEPRESS);
		command->SetDir(glm::vec2(1, 0));

		command = input.AddCommand<dae::ChangeDir>(m_PlayerGO.get(), up, dae::InputManager::KeyPress::SINGLEPRESS);
		command->SetDir(glm::vec2(0, -1));

		command = input.AddCommand<dae::ChangeDir>(m_PlayerGO.get(), down, dae::InputManager::KeyPress::SINGLEPRESS);
		command->SetDir(glm::vec2(0, 1));
	}

private:
	std::shared_ptr<dae::Texture2D> m_Texture{};
	std::shared_ptr<dae::GameObject> m_PlayerGO{};
};