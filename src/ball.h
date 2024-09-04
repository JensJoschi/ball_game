#ifndef BALL_H
#define BALL_H

#include "physicalObject.h"
/** @cond */
#include <SFML/Graphics.hpp>
/** @endcond */

/*! 
    *  \brief Ball class
    *  \details
    *  This class implements a ball that may move and may bounce off objects. 
    */
class Ball: public PhysicalObject {
    public:
    Ball(sf::Vector2f pos, float size, double direction, double vel);
    Ball() = delete; //game does not work with default ball that does not move

    /**
     * \brief move the ball
     * \details
     * Move ball according to laws of physics.
     */
    void moveBall(sf::Time elapsed);

    /*! 
        *  \brief bounce the ball
        *  \details
        *  This function will change the direction of the ball. completely inelastic collision 
        * (no velocity loss, angle of incidence = angle of reflection). This function does not move the ball
    */
    void rebounce(double surfaceAngle);
    private:
    double m_direction; //radians
    double m_velocity;
};


#endif // BALL_H