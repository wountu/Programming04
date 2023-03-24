#include <SDL.h>
#include "InputManager.h"
#include "XInput.h"

bool dae::InputManager::ProcessInput()
{
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

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
		// etc...
	}

	return true;
}

unsigned dae::InputManager::AddController()
{
	unsigned index = static_cast<unsigned int>(m_Controllers.size());
	m_Controllers.push_back(std::make_unique<ControllerXbox>(index));
	return index;
}
