#include "ServiceLocator.h"

namespace dae
{
	SoundSystem& dae::ServiceLocator::GetSoundSystem()
	{
		return *m_SoundSystem;
	}

	void dae::ServiceLocator::RegisterSoundSystem(std::unique_ptr<SoundSystem> soundSystem)
	{
		m_SoundSystem = std::move(soundSystem);
	}
}
