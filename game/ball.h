#pragma once

#include "physicalObject.h"
/** @cond */
#include <SFML/Graphics.hpp>
/** @endcond */
#define M_PI 3.14159265358979323846
/*! 
    *  \brief Ball class
    *  \details
    *  This class implements a ball that may move and may bounce off objects. 
    */
class Ball: public PhysicalObject {
    public:
    Ball(sf::Vector2f pos, float size, double direction, double vel);
    Ball() = delete; //game does not work with default ball that does not move

    void move(sf::Time elapsed) override;
	void changeSpeed(double factor);

    /*! 
        *  \brief bounce the ball
        *  \details
        *  This function will change the direction of the ball. completely inelastic collision 
        * (no velocity loss, angle of incidence = angle of reflection). This function does not move the ball
    */
    void rebounce(double surfaceAngle);
    private:
		double m_direction; //*< direction of the ball in radians */
		double m_velocity;  //*< velocity of the ball */
		sf::Color chooseColor(); //*< choose a random color for the ball */
};