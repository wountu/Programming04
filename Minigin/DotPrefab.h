#pragma once
#include "BasePrefab.h"
#include "RenderComponent.h"
#include "TransformComponent.h"

class DotPrefab final : public BasePrefab
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

		return dot;
	}

	void SetTexture(std::shared_ptr<dae::Texture2D> texture) override
	{
		m_Texture = texture;
	}

private:
	std::shared_ptr<dae::Texture2D> m_Texture{};
};