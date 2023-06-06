#include "SoundEffectSystem.h"
#include "SDL_mixer.h"
#include "ResourceManager.h"
#include "SDL.h"

#include <iostream>

dae::SoundEffectSystem::SoundEffectSystem()
{
	Mix_Init(MIX_INIT_MP3);
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);

	m_IsRunning = true;
	m_Thread = std::jthread{ &SoundEffectSystem::Update, this };
}

dae::SoundEffectSystem::~SoundEffectSystem()
{
	m_IsRunning = false;
	m_Condition.notify_one();

	Mix_CloseAudio();
	Mix_Quit();
}

void dae::SoundEffectSystem::Update()
{
	while (m_IsRunning)
	{

		std::unique_lock lock{ m_Mutex };
		m_Condition.wait(lock, [&]() {

			if (!m_IsRunning)
			return true;

			return !m_SoundQueue.empty();
		});

		if (m_SoundQueue.empty())
			return;
		
		auto sound = m_SoundQueue.front();

		lock.unlock();

		m_SoundQueue.pop();

		if (sound.soundAction == SoundPlay)
		{
			if (sound.isLoaded)
			{
				if (m_Sounds.contains(sound.sound))
				{
					const auto chunck = m_Sounds.at(sound.sound);

					if (Mix_PlayChannel(-1, chunck, 0) == -1)
						std::cout << "Problem trying to play the sound with id --> " << sound.sound << "\n";
				}
			}
			else std::cout << "The sound at id: " << sound.sound << " is not loaded." << "\n";
		}
		
		else if (sound.soundAction == Load)
		{
 			auto path = m_LoadSounds.at(sound.sound);
			if (!path.empty())
			{
				const auto chunck = Mix_LoadWAV(path.c_str());
				if (chunck)
				{
					m_Sounds.emplace(sound.sound, chunck);
					sound.isLoaded = true;
				}
			}
		}
	}
}

void dae::SoundEffectSystem::Play(const sound_id soundId, const float volume)
{
	Sound sound;
	sound.sound = soundId;
	sound.volume = volume;
	sound.soundAction = SoundPlay;

	m_SoundQueue.push(sound);

	m_Condition.notify_one();
}


void dae::SoundEffectSystem::LoadSound(const sound_id id, const std::string& pathName)
{
	Sound sound;
	sound.sound = id;
	sound.soundAction = Load;
	sound.isLoaded = false;

	m_SoundQueue.push(sound);

	auto dataPath = ResourceManager::GetInstance().GetDataPath();
	std::string soundPath = dataPath + pathName;

	m_LoadSounds.emplace(std::pair{ id, soundPath });

	m_Condition.notify_one();
}
