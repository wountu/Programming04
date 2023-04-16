#include "ScoreComponent.h"
#include "GameObject.h"

void dae::ScoreComponent::Initialize(std::shared_ptr<GameObject> parent, int startScore)
{
    m_Parent = parent.get();
    m_Score = startScore;
}

void dae::ScoreComponent::Update()
{
}

void dae::ScoreComponent::Render() const
{
}

int dae::ScoreComponent::GetScore() const
{
    return m_Score;
}

void dae::ScoreComponent::AddScore(int amount)
{
    m_Score += amount;

    m_Parent->NotifyObject(dae::Observer::Event::SCORE_ADDED);

    if (m_Score >= 500)
    {
        m_Parent->NotifyObject(dae::Observer::Event::SCORE_500);
    }
}
