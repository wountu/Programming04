#include "Observer.h"
#include "Achievement.h"
#include "GameObject.h"

#include <isteamuserstats.h>

//void dae::Achievement::Notify(GameObject* actor, Event event)
//{
//}

dae::Achievement::Achievement()
{
	SteamUserStats()->ClearAchievement("ACH_WIN_ONE_GAME");
}

void dae::Achievement::Notify(dae::GameObject*, Event event)
{
	if (event == Event::SCORE_500)
	{
		SteamUserStats()->SetAchievement("ACH_WIN_ONE_GAME");
	}
}

void dae::Achievement::Update()
{
}

void dae::Achievement::Render() const
{
}


