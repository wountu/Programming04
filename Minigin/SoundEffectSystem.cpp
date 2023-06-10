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
			return !m_IsRunning || !m_SoundQueue.empty();
		});

		if (m_SoundQueue.empty())
			continue;
		
		auto sound = m_SoundQueue.front();
		m_SoundQueue.pop();

		lock.unlock();


		auto loadSoundStruct = m_LoadSounds.at(sound.sound);

		if (sound.soundAction == Load)
		{
			
			//auto path = m_LoadSounds.at(sound.sound);
			if (!loadSoundStruct.pathName.empty())
			{
				const auto chunck = Mix_LoadWAV(loadSoundStruct.pathName.c_str());
				if (chunck)
				{
					m_Sounds.emplace(sound.sound, chunck);
					loadSoundStruct.isLoaded = true;
					m_LoadSounds.at(sound.sound) = loadSoundStruct;
					std::cout << "Sound at id: " << sound.sound << " loaded" << "\n";
				}
			}
		}

		if (sound.soundAction == SoundPlay)
		{
			if (loadSoundStruct.isLoaded)
			{
				std::cout << "The sound at id: " << sound.sound << " is loaded and ready to be played \n";
				if (m_Sounds.contains(sound.sound))
				{
					const auto chunck = m_Sounds.at(sound.sound);
					auto channel = Mix_PlayChannel(-1, chunck, 0);
					if (channel == -1)
						std::cout << "Problem trying to play the sound with id --> " << sound.sound << "\n";
				
					Mix_Volume(channel, static_cast<int>(sound.volume));
				}
			}
			else std::cout << "The sound at id: " << sound.sound << " is not loaded." << "\n";
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

	m_SoundQueue.push(sound);

	auto dataPath = ResourceManager::GetInstance().GetDataPath();
	std::string soundPath = dataPath + pathName;

	LoadSoundStruct loadSound;
	loadSound.isLoaded = false;
	loadSound.pathName = soundPath;

	m_LoadSounds.emplace(std::pair{ id, loadSound });

	m_Condition.notify_one();
}
