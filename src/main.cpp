#include "SnakeGame.h"
#include "Shared.h"

int main()
{
	Shared::GetLog().WriteInfo("--------------------------------------------");
	Shared::GetLog().WriteInfo("Hi! Snake game session starting now!");

	const Settings& setts = Shared::GetSettings();

	try
	{
		SnakeGame game;

		game.SetSpaceConfig(setts.GetGridWidth(), setts.GetGridHeight(), setts.GetCellSize());
		game.SetTimingConfig(setts.GetInitInterval(), setts.GetIntervalDecrement());
		game.SetControlConfig(setts.GetDirLeft(), setts.GetDirUp(), setts.GetDirRight(), setts.GetDirDown(), setts.GetControl());
		game.SetStyleShapeConfig(setts.GetMealShape(), setts.GetSnakeShape());
		game.SetModeConfig(setts.IsWrapMode());
		game.SetStyleColorConfig(setts.GetBackgroundColor(), setts.GetSnakeBlockColor(), setts.GetSnakeHeadBlockColor(), 
			setts.GetSnakeOutlineColor(), setts.GetMealColor(), setts.GetMealOutlineColor(), setts.GetScoreTextColor(), 
			setts.GetWelcomeTextColor(), setts.GetGameOverTextColor());

		game.Run();
	}
	catch (std::runtime_error& ex)
	{
		Shared::GetLog().WriteError(ex.what());
	}
	catch (...)
	{
		Shared::GetLog().WriteError("Raised critical exception in snake game. Program aborted");
	}
	
	return 0;
}