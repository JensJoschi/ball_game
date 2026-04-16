#include "menu.h"
#include "game.h"
#include "inputSettings.h"
#include "optionMenu.h"
#include "qtmenu.h"
#include "enums.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cassert>
#include <memory>
#include <QApplication>
#include <QMainWindow>
#include <QStackedWidget>

InputSettings createInput(Controls c, items  i) {
    switch (c) {
    case Controls::KB:
        return InputSettings(ControllerSettings{ 200.0 }, PlayerKBSetupParams(sf::Keyboard::Key::W, sf::Keyboard::Key::S));
    case Controls::MOUSE:
        return InputSettings(ControllerSettings{ 200.0 }, PlayerMouseParams());
    case Controls::AI:
        return InputSettings(ControllerSettings{ 200.0 }, AISetupParams(i));
    default:
        return InputSettings(ControllerSettings{ 200.0 }, PlayerKBSetupParams(sf::Keyboard::Key::W, sf::Keyboard::Key::S));
    }
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    a.setStyleSheet(R"(
        QWidget [highlighted="false"] QLabel {
            color: black;
        }
        QWidget [highlighted="true"] QLabel{
            color: red;
        }
    )");

	QMainWindow* mainWindow = new QMainWindow;
    QStackedWidget* stackedWidget = new QStackedWidget;
    mainWindow->setCentralWidget(stackedWidget);

	QtMenu qtMenu(stackedWidget);
    qtMenu.run();
    mainWindow->show();
    int result = a.exec();
	Options options = qtMenu.getOptions();
	Controls p1 = qtMenu.getP1();
	Controls p2 = qtMenu.getP2();
    delete mainWindow;
	InputSettings p1Settings = createInput(p1, items::P1);
	InputSettings p2Settings = createInput(p2, items::P2);


    float width = 800.0;
    float height = 600.0;
    sf::RenderWindow window(sf::VideoMode(width, height), "Ball game");
    window.setFramerateLimit(60);
    const std::string f = "arial.ttf";
    Menu m{ window, f };
    m.run(); //not using output anymore
 
    Game game(
           options,
           std::move(p1Settings),
		   std::move(p2Settings),
           window);
    game.run();
    std::cout << "game over.";
}