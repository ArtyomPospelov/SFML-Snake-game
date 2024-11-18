#pragma once
#include "Settings.h"
#include "Log.h"
#include <SFML/Window/Keyboard.hpp>

namespace Shared
{
	const Settings& GetSettings();
	Log& GetLog();

	sf::Keyboard::Key TranslateKey(std::string keyName);
	std::string TranslateKey(sf::Keyboard::Key key);
}