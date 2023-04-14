#pragma once
namespace dae
{
	class GameObject;
	class Observer
	{
	public:
		enum class Event
		{
			PLAYER_RECEIVED_DAMAGE,
			PLAYER_DIED,
			SCORE_ADDED,
			SCORE_500
		};

		Observer() = default;
		virtual ~Observer() = default;
		virtual void Notify(GameObject* actor, Event event) = 0;

		virtual void Update() = 0;
		virtual void Render() const = 0;
	};

}
