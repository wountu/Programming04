#pragma once
#include <string>

namespace dae
{
	using sound_id = unsigned short;
	class SoundSystem
	{
	public:
		SoundSystem() = default;
		virtual ~SoundSystem() = default;

		SoundSystem(const SoundSystem& other)			 = delete;
		SoundSystem& operator=(const SoundSystem& other) = delete;
		SoundSystem(SoundSystem&& other)				 = delete;
		SoundSystem& operator=(SoundSystem&& other)		 = delete;

		virtual void Update() = 0;

		virtual void Play(const sound_id id, const float volume) = 0;
		virtual void LoadSound(const sound_id id, const std::string& pathName) = 0;
	};
}

