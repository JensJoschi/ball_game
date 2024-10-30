#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>


struct Options {
    float player1Size{ 50.0 };
    float player2Size{ 50.0 };
    int ballVelocity{ 50 };
	static constexpr size_t element_count = 3; //enum-like counting of elements
};

class OptionsMenu {
public:
	OptionsMenu() = delete;
	OptionsMenu(sf::RenderWindow& window, const Options& options);
	const Options& getOptions() const { return m_options; }
	bool update(const std::vector<sf::Event>& events);

private:
	sf::RenderWindow& m_window;
	sf::Font m_font;
	std::vector<sf::Text> m_menuTexts;
	Options m_options;
	int m_highlighted{ 0 };
	bool handleKey(sf::Event event);
	void display();
	void updateTexts();
};