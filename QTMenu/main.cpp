#include <QApplication>
#include "menu.h"
#include "menuitem.h"

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


    std::vector<MenuItemBase*> items;
    QStringList controls{"Keyboard", "Mouse", "AI"};
    MenuItemBase* item0 = new MenuItemQStrList(QString{"Player1: "}, controls);
    MenuItemBase* item1 = new MenuItemQStrList(QString{"Player2: "}, controls);
    MenuItemBase* item2 = new MenuItemBase(QString{"Options"});
    MenuItemBase* item3 = new MenuItemBase(QString{"Start"});

    items.push_back(item0);
    items.push_back(item1);
    items.push_back(item2);
    items.push_back(item3);

    //takes ownership via parenting
    Menu mainMenu(items, nullptr);
    mainMenu.show();

    MenuItemBase* options0 = new MenuItemInt(QString{"Player1 size: "}, 10);
    MenuItemBase* options1 = new MenuItemInt(QString{"Player2 size: "}, 10);
    MenuItemBase* options2 = new MenuItemInt(QString{"Ball velocity"}, 20);
    MenuItemBase* options3 = new MenuItemBase(QString{"Back"});
    std::vector<MenuItemBase*> optionItems;
    optionItems.push_back(options0);
    optionItems.push_back(options1);
    optionItems.push_back(options2);
    optionItems.push_back(options3);
    Menu optionsMenu(optionItems, nullptr);
    // optionsMenu.show();
    return a.exec();

    //to do: add mainWindow containing stack of windows, use activate() signals,
    //conversion enum control <->string and use of Menu::getStates
    //add mouse over->highlighting
}
