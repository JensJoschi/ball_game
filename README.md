# Overview  
This is a little pong game for demonstration purposes. While it may work, the main objective is to demonstrate various design patterns and best practices. 

A ball is placed in the middle of a field. It moves into a random direction with constant velocity, and it will rebounce from any hard object it encounters. These hard objects are 1) the upper and lower walls, 2) paddles that can be controlled by Player or AI. If the ball moves past the paddle and enters the right/left edge of the field, the opposite site gains a point. 

The number of human players, AI difficulty (if applicable) and sides are chosen at startup. The game is over when the player aborts.

# class overview and design decisions  

![UML overview](/doc/UML.png)

The core of the game consists of a Game object, Ball and Paddle. Balls and Paddles must be movable, visible on screen, and able to collide.

Movement:  

The PhysicalObject class contains the current shape and can be moved around. There are in principle two forms of movement: based on physics (gravity, impulse etc), and based on game mechanics (control by AI, player or power items). The move() function of PhysicalObject is a basic setter that does not contain either, so access is restricted by making it a protected member. The derived classes (Ball, Paddle etc) then add physics and may expose a public function; for movement based on game mechanics, on the other hand, I use a command pattern. Only the commands are friends with PhysicalObject, so only they are able to access the protected setter and move Paddles according to game logic (up or down). In the future, Paddles may include physics-based movement as well, e.g. impulse upon being hit by a ball, gravity etc. Usage of a command patterns separates the physical constraints of movement from those imposed by game logic.

Visibility and collision:  

The PhysicalObject has a shape which is used for displaying and calculating collisions with other shapes. Some observer will be implemented later to allow drawing on screen, being visible to AI etc.

Control:  

Controllers fetch input (from players or AI) and are able to return (or queue) the commands. Game is responsible for matching controller outputs (commands) with a geometry (paddles). 
Game may have its own way of interfering with the objects as well, e.g. using commands on ball to make the ball wiggle, or on paddles to prevent them from leaving the screen. This design allows abstract control of any object, by human, AI or the game environment without entangling the classes.

