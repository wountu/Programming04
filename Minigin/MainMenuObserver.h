#pragma once
#include "Observer.h"
#include "glm/vec2.hpp"
#include "TextObject.h"

#include <memory>

namespace dae
{
	class MainMenuObserver final : public Observer
	{
	public:
		MainMenuObserver() = default;
		~MainMenuObserver() = default;

		MainMenuObserver(const MainMenuObserver& other) = delete;
		MainMenuObserver& operator=(const MainMenuObserver& other) = delete;
		MainMenuObserver(MainMenuObserver&& other) = delete;
		MainMenuObserver& operator=(MainMenuObserver&& other) = delete;

		void Initialize(glm::vec2 pos, std::string startText);

		virtual void HandleEvent(GameObject* actor, Event event) override;
		virtual void OnSubjectDestroy() override;

		virtual void Render() const override;
		virtual void Update() override;
	private:
		std::unique_ptr<TextObject> m_Text{ nullptr };
	};
}

