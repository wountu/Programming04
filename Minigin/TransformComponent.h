#pragma once
#include "BaseComponent.h"
#include <glm/vec2.hpp>

namespace dae
{
	class TransformComponent final : public BaseComponent
	{
	public:
		TransformComponent() = default;
		virtual ~TransformComponent();
		TransformComponent(const TransformComponent& other) = delete;
		TransformComponent& operator=(const TransformComponent& other) = delete;
		TransformComponent(TransformComponent&& other) = delete;
		TransformComponent& operator=(TransformComponent&& other) = delete;

		virtual void Initialize(const glm::vec2& pos, float angle, std::shared_ptr<GameObject> parent);

		virtual void Update() override;

		void ChangeLocalPosition(glm::vec2 pos);

		glm::vec2 GetLocalPosition() const;
		glm::vec2 GetWorldPosition();

		void ChangeAngle(float angle);
		float GetAngle() const;
		glm::vec2 GetDir() const;

		void SetPositionDirty();
	private:
		glm::vec2 m_WorldPosition{};
		glm::vec2 m_LocalPosition{};
		glm::vec2 m_Direction{};
		float m_Angle{};

		bool m_DirtyFlag{};

		GameObject* m_Parent{ nullptr };

		void UpdateWorldPos();
	};

}

