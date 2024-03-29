#pragma once
#include "SoundSystem.h"
#include <vector>
#include <map>
#include <queue>
#include <thread>
#include <condition_variable>

struct Mix_Chunk;

namespace dae
{
	class SoundEffectSystemImpl;

	class SoundEffectSystem final : public SoundSystem
	{
	public:
		SoundEffectSystem();
		virtual ~SoundEffectSystem() override;

		virtual void Update() override;

		virtual void Play(const sound_id id, const float volume) override;
		virtual void LoadSound(const sound_id id, const std::string& pathName) override;
	private:
		enum Action
		{
			SoundPlay,
			Pause,
			Resume,
			Load
		};

		struct Sound
		{
			sound_id sound;
			Action soundAction;
			float volume;
		};

		struct LoadSoundStruct
		{
			std::string pathName;
			bool isLoaded;
		};

		std::map<sound_id, LoadSoundStruct> m_LoadSounds{};

		std::map<sound_id, Mix_Chunk*> m_Sounds{};
		//std::map<sound_id, std::string> m_LoadSounds{};
		//std::map<sound_id, bool> m_SoundLoaded{};

		std::queue <Sound> m_SoundQueue{};

		std::jthread m_Thread;
		std::mutex m_Mutex;
		std::condition_variable m_Condition;

		bool m_IsRunning{};

		std::unique_ptr<SoundEffectSystemImpl> m_pImpl;
	};
}

