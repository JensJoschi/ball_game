#include "menu.h"
#include "game.h"
#include "inputSettings.h"
#include "optionMenu.h"
#include "qtmenu.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cassert>
#include <memory>
#include <QApplication>
#include <QMainWindow>
#include <QStackedWidget>


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

    delete mainWindow;

    float width = 800.0;
    float height = 600.0;
    sf::RenderWindow window(sf::VideoMode(width, height), "Ball game");
    window.setFramerateLimit(60);
    const std::string f = "arial.ttf";
    Menu m{ window, f };
    m.run();
    InputSettings p1{ std::move(*m.getP1()) };
    InputSettings p2{ std::move(*m.getP2()) };
    Game game(
            options,
           std::move(p1),
		   std::move(p2),
           window);
    game.run();
    std::cout << "game over.";
}