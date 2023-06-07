#pragma once
#include "BaseComponent.h"
#include "glm/vec2.hpp"
#include "TransformComponent.h"

namespace dae
{
	class AimComponent final : public BaseComponent
	{
	public:
		AimComponent() = default;
		virtual ~AimComponent() = default;

		AimComponent(const AimComponent& other) = delete;
		AimComponent& operator=(const AimComponent& other) = delete;
		AimComponent(AimComponent&& other) = delete;
		AimComponent& operator=(AimComponent&& other) = delete;

		virtual void Initialize(std::shared_ptr<GameObject> parent);
		virtual void Update() override;
		virtual void Render() const override;
	private:
		GameObject* m_Parent{ nullptr };
		TransformComponent* m_Transform{ nullptr };
	};

}

