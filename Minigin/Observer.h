#pragma once
namespace dae
{
	class GameObject;
	class Observer
	{
	public:
		enum class Event
		{
			PLAYER_DIED,
			SCORE_500
		};

		Observer() = default;
		virtual ~Observer() = default;
		virtual void Notify(GameObject* actor, Event event) = 0;
	};

}
