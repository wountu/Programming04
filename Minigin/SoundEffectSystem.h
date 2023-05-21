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
	class SoundEffectSystem final : public SoundSystem
	{
	public:
		SoundEffectSystem();
		virtual ~SoundEffectSystem() override = default;

		virtual void Update() override;

		virtual void Play(const sound_id id, const float volume) override;
		virtual void LoadSound(const sound_id id, const std::string& pathName) override;
	private:
		std::map<sound_id, Mix_Chunk*> m_Sounds{};
		std::queue<sound_id> m_SoundQueue{};

		std::jthread m_Thread;
		std::mutex m_Mutex;
	};
}

