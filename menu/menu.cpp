
#include <SFML/Graphics.hpp>
#include "menuImpl.h"
#include "menu.h"
#include "inputSettings.h"
#include "options.h"


Menu::Menu(sf::RenderWindow& w, const std::string& fontpath) : m_impl(std::make_unique<MenuImpl>(w, fontpath)){}
Menu::~Menu() = default;
void Menu::run() {m_impl->run();}

const Options& Menu::getOptions() const { return m_impl->getOptions(); }

std::unique_ptr<InputSettings> Menu::getP1() { return m_impl->getP1(); }

std::unique_ptr<InputSettings> Menu::getP2() { return m_impl->getP2(); }



