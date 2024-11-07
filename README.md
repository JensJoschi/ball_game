# Overview  
This is a little pong game for demonstration purposes. While it may work, the main objective is to demonstrate various design patterns and best practices. 

A ball is placed in the middle of a field. It moves into a random direction with constant velocity, and it will rebounce from any hard object it encounters. These hard objects are 1) the upper and lower walls, 2) paddles that can be controlled by Player or AI. If the ball moves past the paddle and enters the right/left edge of the field, the opposite site gains a point. 

The number of human players, AI difficulty (if applicable) and sides are chosen at startup. The game is over when the player aborts.


# How to play
In the main menu, use arrow keys on Player1 and Player2 to choose between Keyboard, Mouse and AI.
Hit Return on Options to set further settings, or on Start to begin the game.
Keys for Keyboard control are W and S for either player. An option to change keybindings will be added later.

# class overview and design decisions  

![UML overview](/doc/UML.png)

The core of the game consists of a Game object, Ball and Paddle. Balls and Paddles must be movable, visible on screen, and able to collide.

**Movement**:  

The PhysicalObject class contains the current shape and can be moved around. There are in principle two forms of movement: based on physics (gravity, impulse etc), and based on 
game mechanics (control by AI, player or power items). The setDestination function of PhysicalObject is a basic setter that does not contain either, so access is restricted by making
it a protected member. The derived classes (Ball, Paddle etc) add physics via the exposed public function move(). Currently, only Ball movement is based on physics, but in the future, 
Paddles may include physics-based movement as well, e.g. impulse upon being hit by a ball, gravity etc.
Game movement mechanics are encapsulated in a command pattern. Commands are friends with PhysicalObject, so only they are able to access the protected setter and move Paddles according
to their own game logic (up or down). Usage of a command patterns separates the physical constraints of movement from those imposed by game logic.

**Visibility and collision:  **

The PhysicalObject has a shape which is used for displaying and calculating collisions with other shapes. GameState tracks the identity of all objects that are currently in the game.
Renderer and AI can query the GameState to draw objects/to react to ball movement. 

**Observers and game state:**  
The game state class is a central registry that can update other classes about the current position and shape of each object. This ensures that all entities react to the same information
and avoids coupling. 
Other notable events are signalled via an observer pattern (e.g. collisions of objects), and the gameState doubles as observer. This allows e.g. counting the total number of game-
wide collisions, and trigger changes in difficulty or color as the game progresses (independent of score). To demonstrate, the game turns cyan as soon as three collisions were detected.

**Control:**  
 
Controllers fetch input (from players or AI) and are able to return (or queue) the commands. Game is responsible for matching controller outputs (commands) with a geometry (paddles). 
Game may have its own way of interfering with the objects as well, e.g. using commands on ball to make the ball wiggle, or on paddles to prevent them from leaving the screen. This design
allows abstract control of any object, by human, AI or the game environment without entangling the classes. Currently implemented controls are keyboard, mouse and AI.

**issues:**  
- ball jumps a bit when hitting a wall, particularly noticeable if hitting at small angles
- keybinding menu to write, possibly also menus for AI difficulty and mouse sensitivity
- memory management: proper deallocation of raw ptrs, or use of smart pointers
- if player uses mouse, paddle moves with constant speed into direction of mouse. Could instantly go to current mouse pos instead, to track the mouse more closely