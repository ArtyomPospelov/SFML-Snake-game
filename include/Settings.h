#pragma once
#include <map>
#include <string>
#include <SFML/Graphics/Color.hpp>

// Settings of snake game.
class Settings final
{
	struct Val
	{
		enum Type
		{
			Int,
			Bool,
			String,
			Color
		} type;

		union Xval
		{
			int i;
			bool b;
			char s[50];
			sf::Color c;

			Xval() {}

		} val;

		Val() {}
		Val(const Val& other) = delete;

		Val(int i)
			: type(Int)
		{
			val.i = i;
		}

		Val(bool b)
			: type(Bool)
		{
			val.b = b;
		}

		Val(const sf::Color& c)
			: type(Color)
		{
			val.c = c;
		}

		Val(const std::string& str)
			: type(String)
		{
			strcpy_s(val.s, str.size(), str.c_str());
		}

		Val(const char* str)
			: type(String)
		{
			strcpy_s(val.s, str);
		}

		void operator=(int i)
		{
			type = Int;
			val.i = i;
		}

		void operator=(bool b)
		{
			type = Bool;
			val.b = b;
		}

		void operator=(const sf::Color c)
		{
			type = Color;
			val.c = c;
		}

		void operator=(const char* str)
		{
			type = String;
			strcpy_s(val.s, str);
		}

		void operator=(const std::string& str)
		{
			type = String;
			strcpy_s(val.s, str.c_str());
		}
	};

public:
	Settings(const char* path);

	inline int GetGridWidth() const { return m_Values.at("GridWidth").val.i; }
	inline int GetGridHeight() const { return m_Values.at("GridHeight").val.i; }
	inline int GetCellSize() const { return m_Values.at("CellSize").val.i; }

	inline int GetInitInterval() const { return m_Values.at("InitialFrameDelay").val.i; }
	inline int GetIntervalDecrement() const { return m_Values.at("FrameDelayDecrement").val.i; }

	inline sf::Color GetBackgroundColor() const { return m_Values.at("Background").val.c; }
	inline sf::Color GetSnakeBlockColor() const { return m_Values.at("SnakeBlock").val.c; }
	inline sf::Color GetSnakeHeadBlockColor() const { return m_Values.at("SnakeHeadBlock").val.c; }
	inline sf::Color GetSnakeOutlineColor() const { return m_Values.at("SnakeOutline").val.c; }
	inline sf::Color GetMealColor() const { return m_Values.at("Meal").val.c; }
	inline sf::Color GetMealOutlineColor() const { return m_Values.at("MealOutline").val.c; }
	inline sf::Color GetScoreTextColor() const { return m_Values.at("ScoreText").val.c; }
	inline sf::Color GetWelcomeTextColor() const { return m_Values.at("WelcomeText").val.c; }
	inline sf::Color GetGameOverTextColor() const { return m_Values.at("GameOverText").val.c; }
	inline std::string GetMealShape() const { return m_Values.at("MealShape").val.s; }
	inline std::string GetSnakeShape() const { return m_Values.at("SnakeShape").val.s; }
	inline bool IsWrapMode() const { return m_Values.at("WrapMode").val.b; }
	inline std::string GetDirLeft() const { return m_Values.at("DirLeft").val.s; }
	inline std::string GetDirUp() const { return m_Values.at("DirUp").val.s; }
	inline std::string GetDirRight() const { return m_Values.at("DirRight").val.s; }
	inline std::string GetDirDown() const { return m_Values.at("DirDown").val.s; }
	inline std::string GetControl() const { return m_Values.at("Control").val.s; }

private:
	std::map<std::string, Val> m_Values;
};