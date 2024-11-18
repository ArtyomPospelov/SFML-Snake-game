#include "Shared.h"
#include <unordered_map>
#include <algorithm>

namespace Shared
{
	const Settings& GetSettings()
	{
		static Settings setts("config.ini");
		return setts;
	}

	Log& GetLog()
	{
		static Log log("log.txt");
		return log;
	}

	sf::Keyboard::Key TranslateKey(std::string keyName)
	{
        static std::unordered_map<std::string, sf::Keyboard::Key> keys {
            { "A", sf::Keyboard::A },
            { "B", sf::Keyboard::B },
            { "C", sf::Keyboard::C },
            { "D", sf::Keyboard::D },
            { "E", sf::Keyboard::E },
            { "F", sf::Keyboard::F },
            { "G", sf::Keyboard::G },
            { "H", sf::Keyboard::H },
            { "I", sf::Keyboard::I },
            { "J", sf::Keyboard::J },
            { "K", sf::Keyboard::K },
            { "L", sf::Keyboard::L },
            { "M", sf::Keyboard::M },
            { "O", sf::Keyboard::O },
            { "P", sf::Keyboard::R },
            { "Q", sf::Keyboard::Q },
            { "R", sf::Keyboard::R },
            { "S", sf::Keyboard::S },
            { "T", sf::Keyboard::T },
            { "U", sf::Keyboard::U },
            { "V", sf::Keyboard::V },
            { "W", sf::Keyboard::W },
            { "Y", sf::Keyboard::Y },
            { "Z", sf::Keyboard::Z },
            { "NUM0", sf::Keyboard::Num0 },
            { "NUM1", sf::Keyboard::Num1 },
            { "NUM2", sf::Keyboard::Num2 },
            { "NUM3", sf::Keyboard::Num3 },
            { "NUM4", sf::Keyboard::Num4 },
            { "NUM5", sf::Keyboard::Num5 },
            { "NUM6", sf::Keyboard::Num6 },
            { "NUM7", sf::Keyboard::Num7 },
            { "NUM8", sf::Keyboard::Num8 },
            { "NUM9", sf::Keyboard::Num9 },
            { "ESCAPE", sf::Keyboard::Escape },
            { "LCTRL", sf::Keyboard::LControl },
            { "LSHIFT", sf::Keyboard::LShift },
            { "LALT", sf::Keyboard::LAlt },
            { "LSYSTEM", sf::Keyboard::LSystem },
            { "RCTRL", sf::Keyboard::RControl },
            { "RALT", sf::Keyboard::RAlt },
            { "RSYSTEM", sf::Keyboard::RSystem },
            { "RSHIFT", sf::Keyboard::RShift },
            { "MENU", sf::Keyboard::Menu },
            { "LBRACKET", sf::Keyboard::LBracket },
            { "RBRACKET", sf::Keyboard::RBracket },
            { "SEMICOLON", sf::Keyboard::Semicolon },
            { "COMMA", sf::Keyboard::Comma },
            { "PERIOD", sf::Keyboard::Period },
            { "APOSTROPHE", sf::Keyboard::Apostrophe },
            { "SLASH", sf::Keyboard::Slash },
            { "BACKSLASH", sf::Keyboard::Backslash },
            { "GRAVE", sf::Keyboard::Grave },
            { "HYPHEN", sf::Keyboard::Hyphen },
            { "SPACE", sf::Keyboard::Space },
            { "ENTER", sf::Keyboard::Enter },
            { "BACKSPACE", sf::Keyboard::Backspace },
            { "TAB", sf::Keyboard::Tab },
            { "PAGEUP", sf::Keyboard::PageUp },
            { "PAGEDOWN", sf::Keyboard::PageDown },
            { "END", sf::Keyboard::End },
            { "HOME", sf::Keyboard::Home },
            { "INSERT", sf::Keyboard::Insert },
            { "DELETE", sf::Keyboard::Delete },
            { "ADD", sf::Keyboard::Add },
            { "MULTIPLY", sf::Keyboard::Multiply },
            { "DIVIDE", sf::Keyboard::Divide },
            { "LEFT", sf::Keyboard::Left },
            { "RIGHT", sf::Keyboard::Right },
            { "UP", sf::Keyboard::Up },
            { "DOWN", sf::Keyboard::Down },
            { "NUMPAD0", sf::Keyboard::Numpad0 },
            { "NUMPAD1", sf::Keyboard::Numpad1 },
            { "NUMPAD2", sf::Keyboard::Numpad2 },
            { "NUMPAD3", sf::Keyboard::Numpad3 },
            { "NUMPAD4", sf::Keyboard::Numpad4 },
            { "NUMPAD5", sf::Keyboard::Numpad5 },
            { "NUMPAD6", sf::Keyboard::Numpad6 },
            { "NUMPAD7", sf::Keyboard::Numpad7 },
            { "NUMPAD8", sf::Keyboard::Numpad8 },
            { "NUMPAD9", sf::Keyboard::Numpad9 },
            { "F1", sf::Keyboard::F1 },
            { "F2", sf::Keyboard::F2 },
            { "F3", sf::Keyboard::F3 },
            { "F4", sf::Keyboard::F4 },
            { "F5", sf::Keyboard::F5 },
            { "F6", sf::Keyboard::F6 },
            { "F7", sf::Keyboard::F7 },
            { "F8", sf::Keyboard::F8 },
            { "F9", sf::Keyboard::F9 },
            { "F10", sf::Keyboard::F10 },
            { "F11", sf::Keyboard::F11 },
            { "F12", sf::Keyboard::F12 },
            { "F13", sf::Keyboard::F13 },
            { "F14", sf::Keyboard::F14 },
            { "F15", sf::Keyboard::F15 },
            { "PAUSE", sf::Keyboard::Pause },
        };

        std::transform(keyName.begin(), keyName.end(), keyName.begin(), std::toupper);

        if (!keys.count(keyName))
            throw std::runtime_error(std::string("Undefined key mnemo: ") + keyName);
        return keys[keyName];
	}

    std::string TranslateKey(sf::Keyboard::Key key)
    {
        switch (key) {

        case sf::Keyboard::A:
            return "A";
        case sf::Keyboard::B:
            return "B";
        case sf::Keyboard::C:
            return "C";
        case sf::Keyboard::D:
            return "D";
        case sf::Keyboard::E:
            return "E";
        case sf::Keyboard::F:
            return "F";
        case sf::Keyboard::G:
            return "G";
        case sf::Keyboard::H:
            return "H";
        case sf::Keyboard::I:
            return "I";
        case sf::Keyboard::J:
            return "J";
        case sf::Keyboard::K:
            return "K";
        case sf::Keyboard::L:
            return "L";
        case sf::Keyboard::M:
            return "M";
        case sf::Keyboard::N:
            return "N";
        case sf::Keyboard::O:
            return "O";
        case sf::Keyboard::P:
            return "P";
        case sf::Keyboard::Q:
            return "Q";
        case sf::Keyboard::R:
            return "R";
        case sf::Keyboard::S:
            return "S";
        case sf::Keyboard::T:
            return "T";
        case sf::Keyboard::U:
            return "U";
        case sf::Keyboard::V:
            return "V";
        case sf::Keyboard::W:
            return "W";
        case sf::Keyboard::X:
            return "X";
        case sf::Keyboard::Y:
            return "Y";
        case sf::Keyboard::Z:
            return "Z";
        case sf::Keyboard::Num0:
            return "Num0";
        case sf::Keyboard::Num1:
            return "Num1";
        case sf::Keyboard::Num2:
            return "Num2";
        case sf::Keyboard::Num3:
            return "Num3";
        case sf::Keyboard::Num4:
            return "Num4";
        case sf::Keyboard::Num5:
            return "Num5";
        case sf::Keyboard::Num6:
            return "Num6";
        case sf::Keyboard::Num7:
            return "Num7";
        case sf::Keyboard::Num8:
            return "Num8";
        case sf::Keyboard::Num9:
            return "Num9";
        case sf::Keyboard::Escape:
            return "Escape";
        case sf::Keyboard::LControl:
            return "LControl";
        case sf::Keyboard::LShift:
            return "LShift";
        case sf::Keyboard::LAlt:
            return "LAlt";
        case sf::Keyboard::LSystem:
            return "LSystem";
        case sf::Keyboard::RControl:
            return "RControl";
        case sf::Keyboard::RShift:
            return "RShift";
        case sf::Keyboard::RAlt:
            return "RAlt";
        case sf::Keyboard::RSystem:
            return "RSystem";
        case sf::Keyboard::Menu:
            return "Menu";
        case sf::Keyboard::LBracket:
            return "LBracket";
        case sf::Keyboard::RBracket:
            return "RBracket";
        case sf::Keyboard::SemiColon:
            return "SemiColon";
        case sf::Keyboard::Comma:
            return "Comma";
        case sf::Keyboard::Period:
            return "Period";
        case sf::Keyboard::Quote:
            return "Quote";
        case sf::Keyboard::Slash:
            return "Slash";
        case sf::Keyboard::BackSlash:
            return "BackSlash";
        case sf::Keyboard::Tilde:
            return "Tilde";
        case sf::Keyboard::Equal:
            return "Equal";
        case sf::Keyboard::Dash:
            return "Dash";
        case sf::Keyboard::Space:
            return "Space";
        case sf::Keyboard::Return:
            return "Return";
        case sf::Keyboard::BackSpace:
            return "BackSpace";
        case sf::Keyboard::Tab:
            return "Tab";
        case sf::Keyboard::PageUp:
            return "PageUp";
        case sf::Keyboard::PageDown:
            return "PageDown";
        case sf::Keyboard::End:
            return "End";
        case sf::Keyboard::Home:
            return "Home";
        case sf::Keyboard::Insert:
            return "Insert";
        case sf::Keyboard::Delete:
            return "Delete";
        case sf::Keyboard::Add:
            return "Add";
        case sf::Keyboard::Subtract:
            return "Subtract";
        case sf::Keyboard::Multiply:
            return "Multiply";
        case sf::Keyboard::Divide:
            return "Divide";
        case sf::Keyboard::Left:
            return "Left";
        case sf::Keyboard::Right:
            return "Right";
        case sf::Keyboard::Up:
            return "Up";
        case sf::Keyboard::Down:
            return "Down";
        case sf::Keyboard::Numpad0:
            return "Numpad0";
        case sf::Keyboard::Numpad1:
            return "Numpad1";
        case sf::Keyboard::Numpad2:
            return "Numpad2";
        case sf::Keyboard::Numpad3:
            return "Numpad3";
        case sf::Keyboard::Numpad4:
            return "Numpad4";
        case sf::Keyboard::Numpad5:
            return "Numpad5";
        case sf::Keyboard::Numpad6:
            return "Numpad6";
        case sf::Keyboard::Numpad7:
            return "Numpad7";
        case sf::Keyboard::Numpad8:
            return "Numpad8";
        case sf::Keyboard::Numpad9:
            return "Numpad9";
        case sf::Keyboard::F1:
            return "F1";
        case sf::Keyboard::F2:
            return "F2";
        case sf::Keyboard::F3:
            return "F3";
        case sf::Keyboard::F4:
            return "F4";
        case sf::Keyboard::F5:
            return "F5";
        case sf::Keyboard::F6:
            return "F6";
        case sf::Keyboard::F7:
            return "F7";
        case sf::Keyboard::F8:
            return "F8";
        case sf::Keyboard::F9:
            return "F9";
        case sf::Keyboard::F10:
            return "F10";
        case sf::Keyboard::F11:
            return "F11";
        case sf::Keyboard::F12:
            return "F12";
        case sf::Keyboard::F13:
            return "F13";
        case sf::Keyboard::F14:
            return "F14";
        case sf::Keyboard::F15:
            return "F15";
        case sf::Keyboard::Pause:
            return "Pause";
        default:
            return "Unknown";
        }
    }
}