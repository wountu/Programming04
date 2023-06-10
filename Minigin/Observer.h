#pragma once
namespace dae
{
	class GameObject;
	class Observer
	{
	public:
		enum Event
		{
			Health_Lost,
			Health_Died
		};

		virtual ~Observer() = default;
		virtual void HandleEvent(GameObject* actor, Event event) = 0;
		virtual void OnSubjectDestroy() = 0;

		virtual void Render() const = 0;
		virtual void Update() = 0;
	};

}
