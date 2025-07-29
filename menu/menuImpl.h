#pragma once
#include "inputSettings.h"
#include "options.h"
#include "optionMenu.h"
#include "mainMenu.h"

#include <SFML/Graphics.hpp>

class MenuImpl {
public:
	MenuImpl(sf::RenderWindow& window, const std::string& fontpath);
	void run();
	const Options& getOptions() const;
	std::unique_ptr<InputSettings> getP1();
	std::unique_ptr<InputSettings> getP2();

private:
	std::unique_ptr<InputSettings> createStandardInput(Controls c, items  i);
	sf::RenderWindow& window;
	std::unique_ptr<OptionsMenu> optionsMenu;
	std::unique_ptr<MainMenu> mainMenu;
	std::unique_ptr<InputSettings> P1Inputs;
	std::unique_ptr<InputSettings> P2Inputs;
};