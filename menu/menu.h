#pragma once

#include <SFML/Graphics.hpp>
#include "inputSettings.h"
#include "options.h"

#ifdef BUILDING_MENU_DLL
#define MENU_API __declspec(dllexport)
#else
#define MENU_API __declspec(dllimport)
#endif
class MenuImpl;
class Menu {
public:
	MENU_API Menu(sf::RenderWindow& window, const std::string& fontpath);
	MENU_API ~Menu();
	MENU_API void run();

	MENU_API const Options& getOptions() const;
	MENU_API std::unique_ptr<InputSettings> getP1();
	MENU_API std::unique_ptr<InputSettings> getP2();

private:
	std::unique_ptr<MenuImpl> m_impl;
};