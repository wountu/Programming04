#pragma once
#include "Observer.h"
#include "glm/vec2.hpp"
#include "TextObject.h"
#include "HealthComponent.h"
#include <memory>

namespace dae
{
	class HealthDisplayObserver final : public Observer
	{
	public:
		HealthDisplayObserver(std::shared_ptr<GameObject> parent, glm::vec2 pos);
		virtual ~HealthDisplayObserver() = default;
		
		HealthDisplayObserver(const HealthDisplayObserver& other)			 = delete;
		HealthDisplayObserver& operator=(const HealthDisplayObserver& other) = delete;
		HealthDisplayObserver(HealthDisplayObserver&& other)				 = delete;
		HealthDisplayObserver& operator=(HealthDisplayObserver&& other)		 = delete;

		virtual void Notify(GameObject* actor, Event event);
		virtual void Update();
		virtual void Render() const;
	private:
		int m_Health{};
		glm::vec2 m_Position{};
		GameObject* m_Parent{ nullptr };

		std::shared_ptr<HealthComponent> m_pHealthComp{ nullptr };
		std::shared_ptr<TextObject> m_pTextObject{ nullptr };
	};
}


