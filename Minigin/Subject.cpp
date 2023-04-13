#include "Subject.h"
#include "GameObject.h"

namespace dae
{
	Subject::~Subject()
	{
		for (auto& observer : m_Observers)
		{
			delete observer;
			observer = nullptr;
		}
	}

	void dae::Subject::AddObserver(Observer* observer)
	{
		m_Observers.push_back(observer);
	}

	void dae::Subject::RemoverObservers(Observer* observer)
	{
		m_Observers.erase(std::remove(m_Observers.begin(), m_Observers.end(), observer), m_Observers.end());
	}

	void dae::Subject::NotifyObserver(GameObject* actor, Observer::Event event)
	{
		for (const auto observer : m_Observers)
		{
			observer->Notify(actor, event);
		}
	}
	void Subject::Update()
	{
		for (auto& observer : m_Observers)
		{
			observer->Update();
		}
	}
	void Subject::Render() const
	{
		for (auto& observer : m_Observers)
		{
			observer->Render();
		}
	}
}

