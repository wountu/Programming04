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

		//Updating/rendering all the observers
		void Update();
		void Render() const;
	private:
		std::vector<Observer*> m_Observers;
	};

}
