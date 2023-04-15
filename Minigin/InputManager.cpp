#include <SDL.h>
#include "InputManager.h"
//#include "XInput.h"

bool dae::InputManager::ProcessInput()
{
	m_PressKeys.clear();

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			auto find = std::find(m_HoldKeys.begin(), m_HoldKeys.end(), e.key.keysym.scancode);
			if (find == m_HoldKeys.end())
			{
				m_HoldKeys.push_back(e.key.keysym.scancode);
				m_PressKeys.push_back(e.key.keysym.scancode);
			}
				
		}
		if (e.type == SDL_KEYUP)
		{
			auto erase = std::find(m_HoldKeys.begin(), m_HoldKeys.end(), e.key.keysym.scancode);
			if(erase != m_HoldKeys.end())
				m_HoldKeys.erase(erase);
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {

		}
		// etc...
	}

	for (auto& controller : m_Controllers)
	{
		controller->Update();
	}

	for (auto& command : m_ConsoleCommands)
	{
		const unsigned& index = command.first.first;
		const ControllerXbox::ControllerInputs& button = command.first.second;
		if (m_Controllers[index]->IsPressed(button))
		{
			command.second->Execute();
		}
	}

	for (auto& command : m_HoldKeyboardCommands)
	{
		auto result = std::find(m_HoldKeys.begin(), m_HoldKeys.end(), command.first);

		if (result != m_HoldKeys.end())
		{
			command.second->Execute();
		}
	}

	for (auto& command : m_PressKeyboardCommands)
	{
		auto result = std::find(m_PressKeys.begin(), m_PressKeys.end(), command.first);

		if (result != m_PressKeys.end())
		{
			command.second->Execute();
		}
	}

	return true;
}

unsigned dae::InputManager::AddController()
{
	unsigned index = static_cast<unsigned int>(m_Controllers.size());
	m_Controllers.push_back(std::make_unique<ControllerXbox>(index));
	return index;
}
