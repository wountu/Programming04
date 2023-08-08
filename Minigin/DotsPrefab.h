#pragma once
#include "BasePrefab.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "CollisionBoxComponent.h"
#include "CollectableComponent.h"

class DotsPrefab final : public BasePrefab
{
public:
	std::shared_ptr<dae::GameObject> Create(glm::vec2 pos) override
	{
		auto dot = std::make_shared<dae::GameObject>();
		dot->Initialize();
		dot->SetTag(dae::Player1);

		auto transform = dot->AddComponent<dae::TransformComponent>();
		transform->Initialize(pos, 0.f, dot);

		assert(m_Texture.get() != nullptr && "dot prefab needs a texture(use SetTexture)");
		auto render = dot->AddComponent<dae::RenderComponent>();
		render->Initialize(m_Texture, dot);

		auto collision = dot->AddComponent<dae::CollisionBoxComponent>();
		collision->Initialize(dot, dae::CollisionBox(pos, static_cast<float>(m_Texture->GetSize().x)
			, static_cast<float>(m_Texture->GetSize().y)), 0);

		auto collectable = dot->AddComponent<dae::CollectableComponent>();
		collectable->Initialize(dot, m_DotScore);

		return dot;
	}

	void SetTexture(std::shared_ptr<dae::Texture2D> texture) override
	{
		m_Texture = texture;
	}

	//Set the score first before creating for the correct score to be used.
	void SetDotScore(int score)
	{
		m_DotScore = score;
	}

private:
	std::shared_ptr<dae::Texture2D> m_Texture{};
	int m_DotScore{ 10 };
};