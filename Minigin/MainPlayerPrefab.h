#pragma once
#include "BasePrefab.h"

#include "GameObject.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "Texture2D.h"
#include "PlayerComponent.h"

class MainPlayerPrefab final : public BasePrefab
{
public:
	std::shared_ptr<dae::GameObject> Create(glm::vec2 pos) override
	{
		auto pacman = std::make_shared<dae::GameObject>();
		pacman->Initialize();
		pacman->SetTag(dae::Player1);

		auto transform = pacman->AddComponent<dae::TransformComponent>();	
		transform->Initialize(pos, 0.f, pacman);

		assert(m_Texture.get() != nullptr && "Pacman prefab needs a texture(use SetTexture)");
		auto render = pacman->AddComponent<dae::RenderComponent>();
		render->Initialize(m_Texture, pacman);

		auto pacmanComp = pacman->AddComponent<dae::PlayerComponent>();
		pacmanComp->Initialize(pacman, 50.f);
		pacmanComp->SetDirection(glm::vec2(-1, 0));

		return pacman;
	}

	void SetTexture(std::shared_ptr<dae::Texture2D> texture) override
	{
		m_Texture = texture;
	}


private:
	std::shared_ptr<dae::Texture2D> m_Texture{};
};