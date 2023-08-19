#pragma once
#include "BasePrefab.h"
#include "TeleporterComponent.h"

class TeleporterPrefab final : public BasePrefab
{
public:
	std::shared_ptr<dae::GameObject> Create(glm::vec2 pos) override
	{
		m_TeleporterGO = std::make_shared<dae::GameObject>();
		m_TeleporterGO->Initialize();
		m_TeleporterGO->SetTag(dae::Static);

		auto transform = m_TeleporterGO->AddComponent<dae::TransformComponent>();
		transform->Initialize(pos, 0.f, m_TeleporterGO);

		auto collision = m_TeleporterGO->AddComponent<dae::CollisionBoxComponent>();
		collision->Initialize(m_TeleporterGO, dae::CollisionBox(pos, 16, 16), 0);
		collision->SetActive(true);

		auto teleporter = m_TeleporterGO->AddComponent<dae::TeleporterComponent>();
		teleporter->Initialize(m_TeleporterGO);

		return m_TeleporterGO;
	}

	void SetTexture(std::shared_ptr<dae::Texture2D> texture) override
	{
	}

private:
	std::shared_ptr<dae::GameObject> m_TeleporterGO{};
};