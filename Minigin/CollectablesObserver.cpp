#include "CollectablesObserver.h"
#include "GameObject.h"

void dae::CollectablesObserver::HandleEvent(GameObject*, Event event)
{
	switch (event)
	{
	case dae::Observer::Collectable_Added:
		++m_Collectables;
		break;
	case dae::Observer::Collectable_Removed:
		--m_Collectables;
		break;
	}

	if (m_Collectables == 0)
	{
		Notify(dae::Observer::Collectables_Pickedup);
	}
}

void dae::CollectablesObserver::OnSubjectDestroy()
{

}

void dae::CollectablesObserver::Render() const
{

}

void dae::CollectablesObserver::Update()
{

}

void dae::CollectablesObserver::AddObserver(std::shared_ptr<dae::Observer> observer)
{
	m_Observers.emplace_back(observer);
}

void dae::CollectablesObserver::RemoveObserver(std::shared_ptr<dae::Observer> observer)
{
	m_Observers.erase(std::remove(m_Observers.begin(), m_Observers.end(), observer), m_Observers.end());
}

void dae::CollectablesObserver::Notify(Observer::Event event)
{
	std::cout << "No collectables left\n";

	for (const auto& observer : m_Observers)
		observer->HandleEvent(nullptr, event);
}

