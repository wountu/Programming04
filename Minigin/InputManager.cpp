#include "InputManager.h"
#include "InputManager.h"
#include <SDL.h>
#include "InputManager.h"
//#include "XInput.h"

bool dae::InputManager::ProcessInput()
{
	m_PressKeys.clear();
	AddInput();

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

	for (auto& command : m_ConsoleCommandsType)
	{
		//Getting the variables
		const unsigned& index = command.first.first.first;
		const ControllerXbox::ControllerInputs& button = command.first.first.second;
		KeyPress pressType = command.second;

		if (pressType == KeyPress::SINGLEPRESS)
		{
			//Look for the button to see if it's been pressed
			const auto& result = std::find(m_PressButtons.begin(), m_PressButtons.end(), button);

			//If it's been pressed before and now isn't being pressed anymore remove it from the container
			if (result != m_PressButtons.end())
			{
				if (m_Controllers[index]->IsUpThisFrame(button))
					m_PressButtons.erase(result);
			}

			//If the button has been pressed for the first time exute it's command and store it in the container
			else
			{
				if (m_Controllers[index]->IsDownThisFrame(button))
				{
					m_PressButtons.emplace_back(button);
					command.first.second->Execute();
				}
			}
		}
		else
		{
			if (m_Controllers[index]->IsPressed(button))
			{
				command.first.second->Execute();
			}
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


	DisableInput();

	return true;
}

void dae::InputManager::AddInput()
{
	//for (const auto& command : m_ConsoleCommandsTypeToAdd)
	//{
	//	m_ConsoleCommandsType.insert(std::move(command));
	//}

	//m_ConsoleCommandsType.insert(std::make_move_iterator(m_ConsoleCommandsTypeToAdd.begin()), std::make_move_iterator(m_ConsoleCommandsTypeToAdd.end()));

	//for (const auto& command : m_ConsoleCommandsTypeToAdd)
	//{
	//	m_ConsoleCommandsType.insert(std::make_pair(command.first, std::move(command.second)));
	//}

	//for (auto& command : m_HoldKeyboardCommandsToAdd)
	//{
	//	m_HoldKeyboardCommands.insert(std::move(command));
	//}

	//for (auto& command : m_PressKeyboardCommandsToAdd)
	//{
	//	m_PressKeyboardCommands.insert(std::move(command));
	//}

	//m_ConsoleCommandsTypeToAdd.clear();
	//m_HoldKeyboardCommandsToAdd.clear();
	//m_PressKeyboardCommandsToAdd.clear();
}

void dae::InputManager::DisableInput()
{
	//Disable commands
	for (auto& command : m_CommandsToDisable)
	{
		for (auto it = m_ConsoleCommandsType.begin(); it != m_ConsoleCommandsType.end(); ++it)
		{
			if (it->first.second.get() == command)
			{
				it = m_ConsoleCommandsType.erase(it);
				break;
			}
		}

		for (auto it = m_PressKeyboardCommands.begin(); it != m_PressKeyboardCommands.end(); ++it)
		{
			if (it->second.get() == command)
			{
				it = m_PressKeyboardCommands.erase(it);
				break;
			}
		}

		for (auto it = m_HoldKeyboardCommands.begin(); it != m_HoldKeyboardCommands.end(); ++it)
		{
			if (it->second.get() == command)
			{
				it = m_HoldKeyboardCommands.erase(it);
				break;
			}
		}
	}
	m_CommandsToDisable.clear();
}

unsigned dae::InputManager::AddController()
{
	unsigned index = static_cast<unsigned int>(m_Controllers.size());
	m_Controllers.push_back(std::make_unique<ControllerXbox>(index));
	return index;
}

void dae::InputManager::RemoveCommand(Command* command)
{
	m_CommandsToDisable.emplace_back(command);
}


