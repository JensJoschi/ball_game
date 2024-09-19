#include "game.h"
#include <SFML/Graphics.hpp>
int main(){
    float width= 800.0;
    float height= 600.0;
    float paddleSize= 40.0;
    int ballVelocity= 100; //pixels per second
    Game g{width, height, paddleSize, paddleSize, ballVelocity};
    g.start();
    g.run();
    return 0;
}