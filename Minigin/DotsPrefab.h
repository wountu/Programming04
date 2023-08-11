#pragma once
#include "BasePrefab.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "CollisionBoxComponent.h"
#include "CollectableComponent.h"
#include "CollectablesObserver.h"
#include "CollectablesObserver.h"

class DotsPrefab final : public BasePrefab
{
public:
	std::shared_ptr<dae::GameObject> Create(glm::vec2 pos) override
	{
		auto dot = std::make_shared<dae::GameObject>();
		dot->Initialize();
		dot->SetTag(dae::Collectable);

		auto transform = dot->AddComponent<dae::TransformComponent>();
		transform->Initialize(pos, 0.f, dot);

		assert(m_Texture.get() != nullptr && "dot prefab needs a texture(use SetTexture)");
		auto render = dot->AddComponent<dae::RenderComponent>();
		render->Initialize(m_Texture, dot);

		auto collision = dot->AddComponent<dae::CollisionBoxComponent>();
		collision->Initialize(dot, dae::CollisionBox(pos, static_cast<float>(m_Texture->GetSize().x)
			, static_cast<float>(m_Texture->GetSize().y)), 3);

		assert(m_Observer.get() != nullptr && "dot prefab needs the collectableObserver(use SetObserver)");
		auto collectable = dot->AddComponent<dae::CollectableComponent>();
		collectable->AddObserver(m_Observer);
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

	void SetDotObserver(std::shared_ptr<dae::CollectablesObserver> observer)
	{
		m_Observer = observer;
	}

private:
	std::shared_ptr<dae::CollectablesObserver> m_Observer;
	std::shared_ptr<dae::Texture2D> m_Texture{};
	int m_DotScore{ 10 };
};