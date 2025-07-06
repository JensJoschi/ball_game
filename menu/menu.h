#include <SFML/Graphics.hpp>

#include "optionMenu.h"
#include "mainMenu.h"
#include "inputSettings.h"


class Menu {
public:
	Menu(sf::RenderWindow& window);
	
	void run();

	const Options& getOptions() const;
	std::unique_ptr<InputSettings> getP1();
	std::unique_ptr<InputSettings> getP2();

private:
	sf::RenderWindow& window;
	std::unique_ptr<OptionsMenu> optionsMenu;
	std::unique_ptr<MainMenu> mainMenu;
	std::unique_ptr<InputSettings> P2Inputs;
	std::unique_ptr<InputSettings> P1Inputs;
};