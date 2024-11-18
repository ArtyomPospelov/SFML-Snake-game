#include "SnakeGame.h"
#include "Random.h"
#include "Shared.h"

#include <iostream>

SnakeGame::SnakeGame()
	: m_KeyboardThread(&SnakeGame::_keyboardHandler, this)
{
	Random::init();
}

SnakeGame::~SnakeGame()
{
	m_KeyboardThread.terminate();
}

void SnakeGame::SetSpaceConfig(size_t griwWidth, size_t gridHeight, size_t cellSize)
{
	m_GridWidth = griwWidth;
	m_GridHeight = gridHeight;
	m_CellSize = cellSize;
}

void SnakeGame::SetTimingConfig(sf::Int32 initInterval, sf::Int32 decrement)
{
	m_InitialInterval = initInterval;
	m_IntevalDecrement = decrement;
}

void SnakeGame::SetStyleColorConfig(const sf::Color& background, const sf::Color& snakeBlock, const sf::Color& snakeHBlock, const sf::Color& snakeOutline, const sf::Color& meal, const sf::Color& mealOutline, const sf::Color& scoreText, const sf::Color& welcomeText, const sf::Color& gameOverText)
{
	m_BackgroundColor = background;
	m_SnakeBlockColor = snakeBlock;
	m_SnakeHeadBlockColor = snakeHBlock;
	m_SnakeOutlineColor = snakeOutline;
	m_SnakeMealColor = meal;
	m_SnakeMealColorOutline = mealOutline;
	m_ScoreTextColor = scoreText;
	m_WelcomeTextColor = welcomeText;
	m_GameOverTextColor = gameOverText;
}

void SnakeGame::SetStyleShapeConfig(std::string mealShape, std::string snakeShape)
{
	auto setShape = [](std::string mnemo, SnakeShape::Type& to) {
		for (auto& ch : mnemo)
			ch = std::toupper(ch);
		if (mnemo == "RECTANGLE")
			to = SnakeShape::T_Rectangle;
		else if (mnemo == "CIRCLE")
			to = SnakeShape::T_Circle;
		else if (mnemo == "TRIANGLE")
			to = SnakeShape::T_Triangle;
		else
			to = SnakeShape::T_Rectangle;
	};

	setShape(mealShape, m_MealShape);
	setShape(snakeShape, m_SnakeShape);
}

void SnakeGame::SetFontPath(const sf::String& path)
{
	m_FontPath = path;
}

void SnakeGame::SetModeConfig(bool isWrapMode)
{
	m_IsWrapMode = isWrapMode;
}

void SnakeGame::SetControlConfig(const sf::String& leftMnemo, const sf::String& upMnemo, const sf::String& rightMnemo, const sf::String& downMnemo, const sf::String& ctrlMnemo)
{
	using Shared::TranslateKey;

	m_LeftKey = TranslateKey(leftMnemo);
	m_UpKey = TranslateKey(upMnemo);
	m_RightKey = TranslateKey(rightMnemo);
	m_DownKey = TranslateKey(downMnemo);
	m_CtrlKey = TranslateKey(ctrlMnemo);
}

void SnakeGame::Run()
{
	auto& log = Shared::GetLog();

	log.WriteInfo("Run game session");

	if (!m_MainFont.loadFromFile(m_FontPath))
		throw std::runtime_error("Fail load game font. Check font file in game directory");

	m_ScoreText = _getText(0.8, "Score 0", m_ScoreTextColor);
	m_ScoreText.setPosition(m_CellSize * m_GridWidth / 2 - m_ScoreText.getCharacterSize() * 6 / 2, 0);
	const int yTextCenter = m_GridHeight * m_CellSize / 2.5;
	std::string gmText = "Game over\nPress @ to new game";
	gmText.replace(gmText.find('@'), 1, Shared::TranslateKey(m_CtrlKey));
	m_GameOverText = _getText(0.9, gmText.c_str(), m_GameOverTextColor);
	m_GameOverText.setPosition(m_CellSize * m_GridWidth / 2 - m_GameOverText.getCharacterSize() * 16 / 2, yTextCenter);
	std::string welText = "Welcome to Snake game\nPress @ to run game";
	welText.replace(welText.find("@"), 1, Shared::TranslateKey(m_CtrlKey));
	m_WelcomeText = _getText(0.8, welText.c_str(), m_WelcomeTextColor);
	m_WelcomeText.setPosition(m_CellSize * m_GridWidth / 2 - m_WelcomeText.getCharacterSize() * 17 / 2, yTextCenter);
	m_PauseText = _getText(0.8, "Paused", m_ScoreTextColor);
	m_PauseText.setPosition(m_ScoreText.getPosition().x, yTextCenter);

	m_KeyboardThread.launch();

	_createNewGame(true);
	create(sf::VideoMode(m_GridWidth* m_CellSize, m_GridHeight* m_CellSize), "Snake game", sf::Style::Close, sf::ContextSettings(0, 0, 8));
	setFramerateLimit(120);

	while (isOpen())
	{
		sf::Event ev;
		while (pollEvent(ev))
		{
			if (ev.type == sf::Event::Closed)
			{
				log.WriteInfo("Close event handled");
				close();
			}
		}

		_drawFrame();
		_processGame();
	}
}

SnakeShape SnakeGame::_instanceSnakeShape(SnakeShape::Type type, size_t initX, size_t initY, int outlineThickness, const sf::Color& color, const sf::Color& outlineColor) const
{
	SnakeShape shape(type, m_CellSize);
	shape.setPosition(initX * m_CellSize, initY * m_CellSize);
	shape.setFillColor(color);

	if (outlineThickness)
	{
		shape.setOutlineThickness(-static_cast<float>(outlineThickness));
		shape.setOutlineColor(outlineColor);
	}

	return shape;
}

sf::Text SnakeGame::_getText(double charKoeff, const char* str, const sf::Color& fillColor) const
{
	sf::Text text;
	text.setFont(m_MainFont);
	text.setFillColor(fillColor);
	text.setString(str);
	text.setCharacterSize(m_CellSize * charKoeff);
	return text;
}

void SnakeGame::_keyboardHandler()
{
	while (1)
	{
		if (sf::Keyboard::isKeyPressed(m_LeftKey))
			m_SnakeDir = Dir::LEFT;
		else if (sf::Keyboard::isKeyPressed(m_UpKey))
			m_SnakeDir = Dir::UP;
		else if (sf::Keyboard::isKeyPressed(m_RightKey))
			m_SnakeDir = Dir::RIGHT;
		else if (sf::Keyboard::isKeyPressed(m_DownKey))
			m_SnakeDir = Dir::DOWN;

		if (sf::Keyboard::isKeyPressed(m_CtrlKey))
		{
			if (m_HandledKey != m_CtrlKey)
			{
				if (m_GameState == GameState::WELCOME)
					m_GameState = GameState::RUN;
				else if (m_GameState == GameState::RUN)
					m_GameState = GameState::PAUSE;
				else if (m_GameState == GameState::PAUSE)
					m_GameState = GameState::RUN;
				else if (m_GameState == GameState::GAMEOVER)
					_createNewGame(false);
			}

			m_HandledKey = m_CtrlKey;
		}
		else
			m_HandledKey = sf::Keyboard::Unknown;

		sf::sleep(sf::milliseconds(10));
	}
}

void SnakeGame::_createNewGame(bool initial)
{
	Shared::GetLog().WriteInfo("Starting new game");

	m_GameState = initial ? GameState::WELCOME : GameState::RUN;
	m_SnakeDir = Dir::UP;
	m_Score = 0;
	m_ProcInterval = m_InitialInterval;
	m_HandledKey = sf::Keyboard::Unknown;
	m_HasEatOnPrevTurn = false;

	m_SnakeBody.clear();
	m_SnakeBody.reserve(100);
	m_SnakeBody.push_back(_instanceSnakeShape(m_SnakeShape, m_GridWidth / 2, m_GridHeight / 2, m_CellSize / 16, m_SnakeHeadBlockColor, m_SnakeOutlineColor));
	m_SnakeMeal = _instanceSnakeShape(m_MealShape, m_GridWidth / 4, m_GridHeight / 4, m_CellSize / 8, m_SnakeMealColor, m_SnakeMealColorOutline);
	m_FrameClock.restart();
}

void SnakeGame::_drawFrame()
{
	clear(m_BackgroundColor);

	for (const sf::Shape& block : m_SnakeBody)
		draw(block);
	draw(m_SnakeBody.front()); // again draw head snake block to strictly indicate head (in any cases).

	draw(m_SnakeMeal);

	m_ScoreText.setString("Score " + std::to_string(m_Score));

	draw(m_ScoreText);

	if (m_GameState == GameState::WELCOME)
		draw(m_WelcomeText);
	else if (m_GameState == GameState::GAMEOVER)
		draw(m_GameOverText);
	else if (m_GameState == GameState::PAUSE)
		draw(m_PauseText);

	display();
}

void SnakeGame::_processGame()
{
	if (m_GameState != GameState::RUN)
		return;

	auto& log = Shared::GetLog();

	if (m_FrameClock.getElapsedTime().asMilliseconds() > m_ProcInterval)
	{
		const int moveStep = static_cast<int>(m_CellSize);
		const int fieldLen = m_CellSize * m_GridWidth;
		sf::Vector2f headPos = m_SnakeBody.front().getPosition();
		const size_t snakeBodySize = m_SnakeBody.size();
		sf::Vector2f afterHeadPos = snakeBodySize > 1 ? m_SnakeBody[1].getPosition() : sf::Vector2f();

		if (m_SnakeDir == Dir::LEFT)
		{
			headPos.x -= moveStep;
			if (snakeBodySize > 1) // prevent snake inversion direction
				if (headPos == afterHeadPos) // if this case, fix position to snake heading position.
				{
					m_SnakeDir = Dir::RIGHT;
					headPos.x += moveStep * 2;
				}
		}
		else if (m_SnakeDir == Dir::UP)
		{
			headPos.y -= moveStep;
			if (snakeBodySize > 1)
				if (headPos == afterHeadPos)
				{
					m_SnakeDir = Dir::DOWN;
					headPos.y += moveStep * 2;
				}
		}
		else if (m_SnakeDir == Dir::RIGHT)
		{
			headPos.x += moveStep;
			if (snakeBodySize > 1)
				if (headPos == afterHeadPos)
				{
					m_SnakeDir = Dir::LEFT;
					headPos.x -= moveStep * 2;
				}
		}
		else if (m_SnakeDir == Dir::DOWN)
		{
			headPos.y += moveStep;
			if (snakeBodySize > 1)
				if (headPos == afterHeadPos)
				{
					m_SnakeDir = Dir::UP;
					headPos.y -= moveStep * 2;
				}
		}

		if (!m_IsWrapMode)
		{
			// check for field edge bump:
			if (headPos.x < 0 || headPos.y < 0 || headPos.x + m_CellSize > fieldLen || headPos.y + m_CellSize > fieldLen)
			{
				log.WriteInfo("Game over. Snake bump in field edge");
				log.WriteInfo("Score is: " + std::to_string(m_Score));
				m_GameState = GameState::GAMEOVER;
				return;
			}
		}

		SnakeShape moveBlock = m_SnakeBody.front();
		moveBlock.setPosition(headPos);
		moveBlock.setFillColor(m_SnakeHeadBlockColor);

		if (m_HasEatOnPrevTurn)
			m_HasEatOnPrevTurn = false;
		else
			m_SnakeBody.pop_back();

		if (!m_SnakeBody.empty())
			m_SnakeBody.front().setFillColor(m_SnakeBlockColor);

		m_SnakeBody.insert(m_SnakeBody.begin(), moveBlock);

		if (m_IsWrapMode)
		{
			for (auto& block : m_SnakeBody)
			{
				auto pos = block.getPosition();
				if (pos.x < 0)
				{
					pos.x = fieldLen - (m_CellSize * (std::abs(pos.x) / m_CellSize));
					block.setPosition(pos);
				}
				else if (pos.y < 0)
				{
					pos.y = fieldLen - (m_CellSize * (std::abs(pos.y) / m_CellSize));
					block.setPosition(pos);
				}
				else if (pos.x + m_CellSize > fieldLen)
				{
					pos.x = (m_CellSize * ((pos.x - fieldLen) / m_CellSize));
					block.setPosition(pos);
				}
				else if (pos.y + m_CellSize > fieldLen)
				{
					pos.y = (m_CellSize * ((pos.y - fieldLen) / m_CellSize));
					block.setPosition(pos);
				}
			}
		}

		// check snake self collusion:
		for (size_t i = 1, c = snakeBodySize; i < c; ++i)
			if (m_SnakeBody[i].getPosition() == m_SnakeBody.front().getPosition())
			{
				log.WriteInfo("Game over. Snake eat some piece of self");
				log.WriteInfo("Score is: " + std::to_string(m_Score));
				m_GameState = GameState::GAMEOVER;
				return;
			}

		// check meal collusion:
		for (const auto& pos : m_SnakeBody)
		{
			while (pos.getPosition() == m_SnakeMeal.getPosition()) // and it it:
			{
				m_SnakeMeal.setPosition(
					static_cast<float>(Random::getRandomInt(0, m_GridWidth - 1) * m_CellSize),
					static_cast<float>(Random::getRandomInt(0, m_GridHeight - 1) * m_CellSize)
				);
				m_HasEatOnPrevTurn = true;
			}
		}

		if (m_HasEatOnPrevTurn)
		{
			++m_Score;
			m_ProcInterval -= m_IntevalDecrement;
		}

		m_FrameClock.restart();
	}
}