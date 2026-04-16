#include "qtmenu.h"
#include "menu.h"
#include "menuitem.h"
#include "enums.h"
#include <QStackedWidget>
#include <QStringList>
#include <cassert>
#include <QApplication>
QtMenu::QtMenu(QStackedWidget* stackedWidget) : stackedWidget(stackedWidget) {
	createMainMenu();
	createOptionsMenu();
}

void QtMenu::createMainMenu() {
	assert(static_cast<int> (Menus::mainMenu) == stackedWidget->count());
	mainMenu = new Menu;
	stackedWidget->addWidget(mainMenu);
	QStringList controls{ "Keyboard", "Mouse", "AI" };
	std::vector<MenuItemBase*> items;
	MenuItemBase* p1 = new MenuItemQStrList(QString{ "Player1: " }, controls);
	MenuItemBase* p2 = new MenuItemQStrList(QString{ "Player2: " }, controls);
	MenuItemBase* optionsItem = new MenuItemBase(QString{ "Options" }, Menus::optionsMenu);
	MenuItemBase* startItem = new MenuItemBase(QString{ "Start" }, Menus::quit);
	items.push_back(p1);
	items.push_back(p2);
	items.push_back(optionsItem);
	items.push_back(startItem);
	mainMenu->addItems(items); 
	QObject::connect(optionsItem, &MenuItemBase::openMenu, stackedWidget, &QStackedWidget::setCurrentIndex); //openMenu signals Menus::optionsMenu (as int)
	QObject::connect(startItem, &MenuItemBase::openMenu, &QCoreApplication::exit); //could add quit menu (quit? yes/no?) instead
}

void QtMenu::createOptionsMenu() {
	assert(static_cast<int> (Menus::optionsMenu) == stackedWidget->count());
	optionsMenu = new Menu;
	stackedWidget->addWidget(optionsMenu);
	std::vector<MenuItemBase*> optionItems;
	MenuItemBase* p1_size = new MenuItemInt(QString{ "Player1 size: " }, 10);
	MenuItemBase* p2_size = new MenuItemInt(QString{ "Player2 size: " }, 10);
	MenuItemBase* ball_v = new MenuItemInt(QString{ "Ball velocity" }, 20);
	MenuItemBase* go_backItem = new MenuItemBase(QString{ "Back" }, Menus::mainMenu);
	optionItems.push_back(p1_size);
	optionItems.push_back(p2_size);
	optionItems.push_back(ball_v);
	optionItems.push_back(go_backItem);
	optionsMenu->addItems(optionItems);
	QObject::connect(go_backItem, &MenuItemBase::openMenu, stackedWidget, &QStackedWidget::setCurrentIndex);
}

void QtMenu::run() {
	assert(mainMenu && optionsMenu && stackedWidget);
	assert(stackedWidget->count() == 2);
	mainMenu->setFocus();
	stackedWidget->show();
}

//const Options& QtMenu::getOptions() const{ //to do
//	assert(false && "qtmenu function not implemented");
//}
//InputSettings QtMenu::getP1() const {
//	//to do
//	assert(false && "qtmenu function not implemented");
//}
//InputSettings QtMenu::getP2() const {
//	//to do
//	assert(false && "qtmenu function not implemented");
//}