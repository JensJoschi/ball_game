#pragma once
#include <QWidget>
#include <QStackedWidget>
#include "options.h"
class InputSettings;
class Menu;
//this is an API, not a QObject: does not parent, does not emit or receive signals
class QtMenu{
public:
	QtMenu(QStackedWidget* stackedWidget);
	~QtMenu() = default; //ownerhship handled by qt parent-child system
	void run();

	const Options& getOptions() const;
	InputSettings getP1() const;
	InputSettings getP2() const;

private:
	Menu* mainMenu; //not owned
	Menu* optionsMenu;
	QStackedWidget* stackedWidget; //also not owned
	void createMainMenu();
	void createOptionsMenu();
};