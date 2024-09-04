#include "ball.h"
#include <SFML/Graphics.hpp>

int main(){
Ball b(sf::Vector2f(0,0), 10, 0, 3);
sf::Time t;
b.moveBall(t);
}