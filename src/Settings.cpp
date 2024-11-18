#include "Settings.h"
#include "inicpp.h"
#include "Shared.h"

Settings::Settings(const char* path)
{
	m_Values["GridWidth"] = 15;
	m_Values["GridHeight"] = 15;
	m_Values["CellSize"] = 25;
	m_Values["InitialFrameDelay"] = 300;
	m_Values["FrameDelayDecrement"] = 10;
	m_Values["Background"] = sf::Color(173, 223, 82);
	m_Values["SnakeBlock"] = sf::Color(0, 147, 1);
	m_Values["SnakeHeadBlock"] = sf::Color(169, 184, 16);
	m_Values["SnakeOutline"] = sf::Color(1, 15, 0);
	m_Values["Meal"] = sf::Color(198, 1, 1);
	m_Values["MealOutline"] = sf::Color(154, 0, 0);
	m_Values["ScoreText"] = sf::Color(83, 186, 47);
	m_Values["WelcomeText"] = sf::Color(0, 177, 1);
	m_Values["GameOverText"] = sf::Color(255, 0, 0);
	m_Values["UseRoundedMeal"] = false;
	m_Values["UseRoundedSnake"] = false;
	m_Values["WrapMode"] = false;
	m_Values["DirLeft"] = "Left";
	m_Values["DirUp"] = "Up";
	m_Values["DirRight"] = "Right";
	m_Values["DirDown"] = "Down";
	m_Values["Control"] = "F2";
	m_Values["MealShape"] = "RECTANGLE";
	m_Values["SnakeShape"] = "RECTANGLE";

	Log& log = Shared::GetLog();

	try
	{
		log.WriteInfo("Reading game config.");
		ini::IniFile ini(path);

		if (ini.count("Space"))
		{
			log.WriteInfo("Reading game field space config");

			m_Values["GridWidth"] = ini["Space"]["GridWidth"].as<int>();
			if (m_Values["GridWidth"].val.i < 5)
				m_Values["GridWidth"].val.i = 5;
			else if (m_Values["GridWidth"].val.i > 500)
				m_Values["GridWidth"].val.i = 500;

			m_Values["GridHeight"] = ini["Space"]["GridHeight"].as<int>();
			if (m_Values["GridHeight"].val.i < 5)
				m_Values["GridHeight"].val.i = 5;
			else if (m_Values["GridHeight"].val.i > 500)
				m_Values["GridHeight"].val.i = 500;

			m_Values["CellSize"] = ini["Space"]["CellSize"].as<int>();
			if (m_Values["CellSize"].val.i < 10)
				m_Values["CellSize"].val.i = 10;
			else if (m_Values["CellSize"].val.i > 50)
				m_Values["CellSize"].val.i = 50;
		}
		else
			log.WriteInfo("Space section config not found");

		if (ini.count("Timing"))
		{
			log.WriteInfo("Reading game timing config");

			m_Values["InitialFrameDelay"] = ini["Timing"]["InitialFrameDelay"].as<int>();
			if (m_Values["InitialFrameDelay"].val.i < 10)
				m_Values["InitialFrameDelay"].val.i = 10;
			else if (m_Values["InitialFrameDelay"].val.i > 1000)
				m_Values["InitialFrameDelay"].val.i = 1000;

			m_Values["FrameDelayDecrement"] = ini["Timing"]["FrameDelayDecrement"].as<int>();
			if (m_Values["FrameDelayDecrement"].val.i < 1)
				m_Values["FrameDelayDecrement"].val.i = 1;
			else if (m_Values["FrameDelayDecrement"].val.i >= m_Values["FrameDelayDecrement"].val.i)
				m_Values["FrameDelayDecrement"].val.i = m_Values["FrameDelayDecrement"].val.i - 1;
		}
		else
			log.WriteInfo("Timing section config not found");

		if (ini.count("Style"))
		{
			log.WriteInfo("Reading game style config");

			auto parseColor = [](const std::string& str, Val& sett) {

				bool r_set = false, g_set = false, b_set = false;
				for (int i = 0, l = 0, c = str.size(); i < c; ++i)
				{
					if (str[i] == ',')
					{
						auto part = str.substr(l, i - l);
						if (!std::any_of(part.begin(), part.end(), [](char ch) { return std::isdigit(ch) || std::isspace(ch); }))
							return false;

						if (!r_set)
						{
							sett.val.c.r = std::atoi(part.c_str());
							r_set = true;
						}
						else if (!g_set)
						{
							sett.val.c.g = std::atoi(part.c_str());
							g_set = true;
						}

						else if (b_set)
						{
							sett.val.c.b = std::atoi(part.c_str());
							b_set = true;
						}

						++(l = i);
					}
				}

				return true;
				};

			parseColor(ini["Style"]["Background"].as<std::string>(), m_Values["Background"]);
			parseColor(ini["Style"]["SnakeBlock"].as<std::string>(), m_Values["SnakeBlock"]);
			parseColor(ini["Style"]["SnakeHeadBlock"].as<std::string>(), m_Values["SnakeHeadBlock"]);
			parseColor(ini["Style"]["SnakeOutline"].as<std::string>(), m_Values["SnakeOutline"]);
			parseColor(ini["Style"]["Meal"].as<std::string>(), m_Values["Meal"]);
			parseColor(ini["Style"]["MealOutline"].as<std::string>(), m_Values["MealOutline"]);
			parseColor(ini["Style"]["ScoreText"].as<std::string>(), m_Values["ScoreText"]);
			parseColor(ini["Style"]["WelcomeText"].as<std::string>(), m_Values["WelcomeText"]);
			parseColor(ini["Style"]["GameOverText"].as<std::string>(), m_Values["GameOverText"]);

			m_Values["MealShape"] = ini["Style"]["MealShape"].as<std::string>();
			m_Values["SnakeShape"] = ini["Style"]["SnakeShape"].as<std::string>();
		}
		else
			log.WriteInfo("Style sections config not found");

		if (ini.count("Mode"))
		{
			log.WriteInfo("Reading game mode config");

			m_Values["WrapMode"] = ini["Mode"]["WrapMode"].as<bool>();
		}

		if (ini.count("Control"))
		{
			log.WriteInfo("Reading control config");

			m_Values["DirLeft"] = ini["Control"]["DirLeft"].as<std::string>();
			m_Values["DirUp"] = ini["Control"]["DirUp"].as<std::string>();
			m_Values["DirRight"] = ini["Control"]["DirRight"].as<std::string>();
			m_Values["DirDown"] = ini["Control"]["DirDown"].as<std::string>();
			m_Values["Control"] = ini["Control"]["Control"].as<std::string>();
		}

		log.WriteInfo("End read config.");
	}
	catch (const std::exception& ex)
	{
		log.WriteError("Fail rading game config. (Some settings may be indispensable): " + std::string(ex.what()));
	}
	catch (...)
	{
		log.WriteError("Fail reading game config (Some settings may be indispensable): Undefined exception.");
	}
}