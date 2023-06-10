#pragma once
namespace dae
{
	class PlayerState
	{
	public:
		virtual ~PlayerState() = default;

		virtual void OnEnter() = 0;
		virtual PlayerState* HandleInput() = 0;
		virtual void OnExit() = 0;
	};
}