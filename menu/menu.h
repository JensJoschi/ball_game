#include <SFML/Graphics.hpp>

#include "optionMenu.h"
#include "mainMenu.h"
#include "inputSettings.h"

#ifdef BUILDING_MENU_DLL
#define MENU_API __declspec(dllexport)
#else
#define MENU_API __declspec(dllimport)
#endif

class Menu {
public:
	MENU_API Menu(sf::RenderWindow& window, const std::string& fontpath);
	
	MENU_API void run();

	MENU_API const Options& getOptions() const;
	MENU_API std::unique_ptr<InputSettings> getP1();
	MENU_API std::unique_ptr<InputSettings> getP2();

private:
	sf::RenderWindow& window;
	std::unique_ptr<OptionsMenu> optionsMenu;
	std::unique_ptr<MainMenu> mainMenu;
	std::unique_ptr<InputSettings> P1Inputs;	
	std::unique_ptr<InputSettings> P2Inputs;
};