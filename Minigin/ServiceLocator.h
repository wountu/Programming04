#pragma once
#include "Singleton.h"
#include "SoundSystem.h"

#include <memory>

namespace dae
{
	class ServiceLocator final
	{
	public:
		static SoundSystem& GetSoundSystem();
		static void RegisterSoundSystem(std::unique_ptr<SoundSystem> soundSystem);
	private:
		inline static std::unique_ptr<SoundSystem> m_SoundSystem;
	};
}