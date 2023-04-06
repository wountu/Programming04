#pragma once
#include <vector>
#include "Observer.h"
namespace dae
{
	class GameObject;
	class Subject
	{
	public:
		Subject() = default;
		~Subject();

		//Observers
		void AddObserver(Observer* observer);
		void RemoverObservers(Observer* observer);
		void NotifyObserver(GameObject* actor, Observer::Event event);
	private:
		std::vector<Observer*> m_Observers;
	};

}
