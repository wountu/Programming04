#include "Command.h"
#include "TransformComponent.h"

namespace dae
{
	MovementRight::MovementRight(GameObject* pActor)
		:Command(pActor)
	{
		m_pTransform = pActor->GetComponent<TransformComponent>().get();
	}

	void MovementRight::Execute()
	{
		std::cout << "test" << "\n";
	}
}