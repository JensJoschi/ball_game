#include <QApplication>
#include <QMainWindow>
#include <QStackedWidget>
#include <QComboBox>
#include "menu.h"
#include "menuitem.h"
#include "helpers.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyleSheet(R"(
        QWidget [highlighted="false"] QLabel {
            color: black;
        }
        QWidget [highlighted="true"] QLabel{
            color: red;
        }
    )");

    QMainWindow mainWindow;
    QStackedWidget* stackedWidget = new QStackedWidget;
    mainWindow.setCentralWidget(stackedWidget);
    //construct main menu:
    Menu* mainMenu = new Menu;
    assert(static_cast<int> (Menus::mainMenu) == 0);
    stackedWidget->addWidget(mainMenu);
    QStringList controls{"Keyboard", "Mouse", "AI"};
    std::vector<MenuItemBase*> items;
    MenuItemBase* p1 = new MenuItemQStrList(QString{"Player1: "}, controls);
    MenuItemBase* p2 = new MenuItemQStrList(QString{"Player2: "}, controls);
    MenuItemBase* optionsItem = new MenuItemBase(QString{"Options"}, Menus::optionsMenu);
    MenuItemBase* startItem = new MenuItemBase(QString{"Start"}, Menus::quit);
    items.push_back(p1);
    items.push_back(p2);
    items.push_back(optionsItem);
    items.push_back(startItem);
    mainMenu->addItems(items);

    //Options menu:
    Menu* optionsMenu = new Menu;
    stackedWidget->addWidget(optionsMenu);
    assert(static_cast<int> (Menus::optionsMenu) == 1);
    std::vector<MenuItemBase*> optionItems;
    MenuItemBase* p1_size = new MenuItemInt(QString{"Player1 size: "}, 10);
    MenuItemBase* p2_size = new MenuItemInt(QString{"Player2 size: "}, 10);
    MenuItemBase* ball_v  = new MenuItemInt(QString{"Ball velocity"}, 20);
    MenuItemBase* go_backItem = new MenuItemBase(QString{"Back"}, Menus::mainMenu);
    optionItems.push_back(p1_size);
    optionItems.push_back(p2_size);
    optionItems.push_back(ball_v);
    optionItems.push_back(go_backItem);
    optionsMenu->addItems(optionItems);

    mainMenu->setFocus();
    mainWindow.show();

    QObject::connect(optionsItem, &MenuItemBase::openMenu, stackedWidget, &QStackedWidget::setCurrentIndex); //signal returns id of Menus::optionMenu (1)
    QObject::connect(go_backItem, &MenuItemBase::openMenu, stackedWidget, &QStackedWidget::setCurrentIndex); //Menus::mainMenu == 0
    QObject::connect(startItem,  &MenuItemBase::openMenu, &a, &QApplication::exit); //could add quit menu (quit? yes/no?) instead
    return a.exec();

    //start game here
//to do
    //conversion enum control <->string and use of Menu::getStates
    //add mouse over->highlighting
}
