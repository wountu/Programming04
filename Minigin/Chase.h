#pragma once
#include "State.h"
#include "AIComonent.h"

namespace dae
{
	class Chase final : public State
	{
	public:
		Chase() = default;
		virtual ~Chase() = default;

		Chase(const Chase& other) = delete;
		Chase& operator=(const Chase& other) = delete;
		Chase(Chase&& other) = delete;
		Chase& operator =(Chase&& other) = delete;

		void Initialize(AIComponent* ai);

		virtual void OnEnter() override;
		virtual State* Update() override;
		virtual void OnExit() override;
	private:
		AIComponent* m_AI{};
	};

}

