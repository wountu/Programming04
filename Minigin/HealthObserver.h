#pragma once
#include "Observer.h"
#include "TextObject.h"

#include <memory>
namespace dae
{
	class TextObject;
	class HealthObserver final : public Observer
	{
	public:
		HealthObserver(glm::vec2 pos, int startLives);
		~HealthObserver() = default;

		HealthObserver(const HealthObserver& other) = delete;
		HealthObserver& operator=(const HealthObserver& other) = delete;
		HealthObserver(HealthObserver&& other) = delete;
		HealthObserver& operator=(HealthObserver&& other) = delete;

		virtual void HandleEvent(GameObject* actor, Event event) override;
		virtual void OnSubjectDestroy() override;

		virtual void Render() const override;
		virtual void Update() override;
	private:
		std::string m_LivesDisplay{};
		std::unique_ptr<TextObject> m_Text{ nullptr };
		int m_Lives{};
	};
}
