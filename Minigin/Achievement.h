#pragma once
#include "Observer.h"
namespace dae
{
	class GameObject;
	//class Observer;
	class Achievement final : public Observer
	{
	public:
		Achievement() = default;

		virtual void Notify(dae::GameObject* actor, Event event);

		virtual void Update();
		virtual void Render() const;
	private:
	};

}

