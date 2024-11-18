#pragma once
#include "SnakeShape.h"

#include <SFML/Graphics.hpp>
#include <SFML/System/Thread.hpp>
#include <vector>

class SnakeGame : public sf::RenderWindow
{
	enum class Dir
	{
		NONE,
		UP,
		LEFT,
		RIGHT,
		DOWN
	};

	enum class GameState
	{
		WELCOME,
		PAUSE,
		RUN,
		GAMEOVER
	};

public:
	SnakeGame();
	~SnakeGame();

	void SetSpaceConfig(size_t griwWidth, size_t gridHeight, size_t cellSize);
	void SetTimingConfig(sf::Int32 initInterval, sf::Int32 decrement);
	void SetStyleColorConfig(const sf::Color& background, const sf::Color& snakeBlock, const sf::Color& snakeHBlock, const sf::Color& snakeOutline, const sf::Color& meal, const sf::Color& mealOutline, const sf::Color& scoreText, const sf::Color& welcomeText, const sf::Color& gameOverText);
	void SetStyleShapeConfig(std::string mealShape, std::string snakeShape);
	void SetFontPath(const sf::String& path);
	void SetModeConfig(bool isWrapMode);
	void SetControlConfig(const sf::String& leftMnemo, const sf::String& upMnemo, const sf::String& rightMnemo, const sf::String& downMnemo, const sf::String& ctrlMnemo);

	void Run();

private:
	SnakeShape _instanceSnakeShape(SnakeShape::Type type, size_t initX, size_t initY, int outlineThickness, const sf::Color& color, const sf::Color& outlineColor) const;
	sf::Text _getText(double charKoeff, const char* str, const sf::Color& fillColor) const;

	void _keyboardHandler();

	void _createNewGame(bool initial);

	void _drawFrame();
	void _processGame();

private:
	size_t m_GridWidth = 20;
	size_t m_GridHeight = 20;
	size_t m_CellSize = 25;
	sf::Int32 m_InitialInterval = 300;
	sf::Int32 m_IntevalDecrement = 10;

	sf::Color m_BackgroundColor = sf::Color(173, 223, 82);
	sf::Color m_SnakeBlockColor = sf::Color(0, 147, 1);
	sf::Color m_SnakeHeadBlockColor = sf::Color(169, 184, 16);
	sf::Color m_SnakeOutlineColor = sf::Color(1, 15, 0);
	sf::Color m_SnakeMealColor = sf::Color(198, 1, 1);
	sf::Color m_SnakeMealColorOutline = sf::Color(154, 0, 0);
	sf::Color m_ScoreTextColor = sf::Color(83, 186, 47);
	sf::Color m_WelcomeTextColor = sf::Color(0, 177, 1);
	sf::Color m_GameOverTextColor = sf::Color(255, 0, 0);
	sf::Font m_MainFont;
	sf::String m_FontPath = "Font";

	SnakeShape::Type m_SnakeShape = SnakeShape::T_Rectangle;
	SnakeShape::Type m_MealShape = SnakeShape::T_Rectangle;

	GameState m_GameState = GameState::WELCOME;
	Dir m_SnakeDir = Dir::UP;
	int m_Score = 0;
	int m_ProcInterval = 0;
	bool m_HasEatOnPrevTurn = false;
	sf::Keyboard::Key m_HandledKey = sf::Keyboard::Unknown;
	std::vector<SnakeShape> m_SnakeBody;
	SnakeShape m_SnakeMeal;
	sf::Thread m_KeyboardThread;
	sf::Clock m_FrameClock;
	sf::Clock m_TimeClock;
	sf::Text m_ScoreText;
	sf::Text m_WelcomeText;
	sf::Text m_GameOverText;
	sf::Text m_PauseText;

	bool m_IsWrapMode = false;

	sf::Keyboard::Key m_LeftKey = sf::Keyboard::Left;
	sf::Keyboard::Key m_UpKey = sf::Keyboard::Up;
	sf::Keyboard::Key m_RightKey = sf::Keyboard::Right;
	sf::Keyboard::Key m_DownKey = sf::Keyboard::Down;
	sf::Keyboard::Key m_CtrlKey = sf::Keyboard::F2;
};