#pragma once
#include "BasePrefab.h"
#include "Texture2D.h"
#include "RenderComponent.h"
#include "AIComonent.h"

class GhostsPrefab final : public BasePrefab
{
public:
	std::shared_ptr<dae::GameObject> Create(glm::vec2 pos) override
	{
		m_Ghost = std::make_shared<dae::GameObject>();
		m_Ghost->Initialize();
		m_Ghost->SetTag(dae::Enemy);

		auto transform = m_Ghost->AddComponent<dae::TransformComponent>();
		transform->Initialize(pos, 0.f, m_Ghost);

		assert(m_Texture.get() != nullptr && "Pacman prefab needs a texture(use SetTexture())");
		auto render = m_Ghost->AddComponent<dae::RenderComponent>();
		render->Initialize(m_Texture, m_Ghost);

		auto ai = m_Ghost->AddComponent<dae::AIComponent>();
		ai->Initialize(m_Ghost);

		return m_Ghost;
	}

	void SetTexture(std::shared_ptr<dae::Texture2D> texture) override
	{
		m_Texture = texture;
	}

private:
	std::shared_ptr<dae::Texture2D> m_Texture{};
	std::shared_ptr<dae::GameObject> m_Ghost{};
};