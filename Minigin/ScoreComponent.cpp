#include "ScoreComponent.h"
#include "GameObject.h"


dae::ScoreComponent::~ScoreComponent()
{
    //for (auto& observer : m_pObservers)
    //    delete observer;

    //m_pObservers.clear();
}

void dae::ScoreComponent::Initialize(std::shared_ptr<GameObject> parent, int startScore)
{
    m_Parent = parent.get();
    m_Score = startScore;
}

void dae::ScoreComponent::Update()
{
    for (const auto& observer : m_pObservers)
        observer->Update();
}

void dae::ScoreComponent::Render() const
{
    for (const auto& observer : m_pObservers)
        observer->Render();
}

void dae::ScoreComponent::AddObserver(Observer* observer)
{
    m_pObservers.emplace_back(observer);
}

void dae::ScoreComponent::RemoveObserver(Observer* observer)
{
    m_pObservers.erase(std::remove(m_pObservers.begin(), m_pObservers.end(), observer), m_pObservers.end());
}

int dae::ScoreComponent::GetScore() const
{
    return m_Score;
}

void dae::ScoreComponent::AddScore(int amount)
{
    m_Score += amount;
    Notify(Observer::Score_Add);
}


void dae::ScoreComponent::Notify(Observer::Event event)
{
    for (const auto& observer : m_pObservers)
    {
        observer->HandleEvent(m_Parent, event);
    }
}
