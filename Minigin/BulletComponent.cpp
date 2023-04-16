#include "BulletComponent.h"
#include "TimeClass.h"

void dae::BulletComponent::Initialize(std::shared_ptr<GameObject> parent, glm::vec2 direction)
{
	m_Parent = parent.get();
	m_Direction = direction;

	m_Transform = m_Parent->GetComponent<TransformComponent>().get();
	auto test = m_Transform->GetPosition();
	std::cout << test.x << ", " << test.y << "\n";
}

void dae::BulletComponent::Update()
{
	if (!m_FirstFrame)
	{
		const float speed{ 50.f };
		auto& timeClass = TimeClass::GetInstance();

		auto oldPos = m_Transform->GetPosition();
		auto offset = (speed * m_Direction * timeClass.GetElapsed());
		glm::vec2 newPos = oldPos + offset;

		std::cout << offset.x << ", " << offset.y << "\n";

		m_Transform->ChangePosition(newPos);
	}
	else m_FirstFrame = false;

}

void dae::BulletComponent::Render() const
{
}
