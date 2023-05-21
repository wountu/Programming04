#include "SoundEffectSystem.h"
#include "SDL_mixer.h"
#include "ResourceManager.h"
#include "SDL.h"

#include <iostream>


dae::SoundEffectSystem::SoundEffectSystem()
{
	Mix_Init(MIX_INIT_MP3);
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);
}

void dae::SoundEffectSystem::Update()
{
	std::unique_lock lock{ m_Mutex };

	while (!m_SoundQueue.empty())
	{
		auto soundId = m_SoundQueue.front();

		std::cout << "Sound being played with id --> " << soundId << "\n";

		Mix_Chunk* sound = m_Sounds.at(soundId);

		if (Mix_PlayChannel(-1, sound, 0) == -1)
			std::cout << "Problem trying to play the sound with id --> " << soundId << "\n";

		m_SoundQueue.pop();
	}
}

void dae::SoundEffectSystem::Play(const sound_id id, const float /*volume*/)
{
	if (!m_Sounds.contains(id))
		return;

	m_SoundQueue.push(id);

	m_Thread = std::jthread{ &SoundEffectSystem::Update, this };
	m_Thread.detach();
}

void dae::SoundEffectSystem::LoadSound(const sound_id id, const std::string& pathName)
{
	//Mix_Chunk* sound = dae::ResourceManager::GetInstance().LoadSound(pathName).get();

	std::string fullPath = dae::ResourceManager::GetInstance().GetDataPath() + pathName;
	Mix_Chunk* sound = Mix_LoadWAV(fullPath.c_str());
	if(!sound)
		std::cout << Mix_GetError() << "\n";
	

	m_Sounds.emplace(std::pair{id, sound });
}
