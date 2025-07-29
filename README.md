# Overview  
This is a little pong game for demonstration purposes. While it may work, the main objective is to demonstrate various design patterns and best practices. 

A ball is placed in the middle of a field. It moves into a random direction with constant velocity, and it will rebounce from any hard object it encounters. These hard objects are 1) the upper and lower walls, 2) paddles that can
be controlled by Player or AI. If the ball moves past the paddle and enters the right/left edge of the field, the opposite site gains a point. 

A menu is shown at startup, letting the user adjust the number of human players, constrols, AI difficulty (if applicable) and sides. The game is over when the player aborts. After every 15 collisions (irrespective of score), the speed is increased and a new ball is placed.


# How to play
In the main menu, use arrow keys on Player1 and Player2 to choose between Keyboard, Mouse and AI.
Hit Return on Options to set further settings, or on Start to begin the game.
Keys for Keyboard control are W and S for either player. An option to change keybindings will be added later.

# Repository overview  
The game menu and the game itself are built as shared libraries (dll). A main executable is placed in the root folder, and CMake is used to compile. Folders:  
- doc: resources for this documentation
- Game: builds the game as shared library (dll)
- include: header files
- menu: builds the menu as shared library (dll)
- tests: unit tests for the game

# class overview and design decisions  

## Menu  

All menus derive from a common base class (MenuBase) which allows displaying, scrolling through and highlighting text items. The return type of its update function is an enum (Windows), describing which menu shall be opened next.   
InputSettings and Options: see section "Shared objects" below.

![UML overview](doc/menu.png)

The main Menu saves the current selection of player types, the optionsMenu current general options (speed, paddle size), and a future Keyboard menu will save keybindings.  
The main class Menu is actually called MenuImpl in the code (Menu is the public-facing API), shortened here for clarity. It contains all menus and manages switching between them, and it responds to external queries.  
The menu will only be called once. To avoid unneccesary copies and clarify ownership, objects are moved upon query (not yet for options, passed as const ref). 

## Shared objects  
Shared objects concern the controller settings and options, which are output of the menu, and input to the game.  

![UML overview](doc/structs.png)
InputSettings contains a general and a controller-specific part. Std::variant is used to store the controller-specific part (Keyboard, Mouse, AI) in a single object.  
Because all shared objects are simple structs, they are trivially movable.

## Game    
The core of the game consists of a Game object, Ball and Paddle. Balls and Paddles must be movable, visible on screen, and able to collide. The game additionally needs inputs regarding general settings (ball speed) and type of control (AI/keyboard,mouse).

![UML overview](doc/game.png)  

**Inputs to Game**  
The game (GameImpl in the code) requires controller settings and options upon startup. These structs are passed by value (options currently as const ref) and moved to the appropriate object (zero-copy transfer); the inputSettings struct is decomposed and the variant resolved in the process.The settings end up in the Controller class, with general settings in the base Controller and specific settings in the appropriate derived class (AI/PlayerKB/PlayerMouse). The Controller classes are used to store/cue movement commands (see below).

**Visibility and collision**  
The PhysicalObject has a shape which is used for displaying and calculating collisions with other shapes. GameState tracks the identity of all objects that are currently in the game.
Renderer and AI can query the GameState to draw objects/to react to ball movement. 

**Observers and game state:**  
The game state class is a central registry that can update other classes about the current position and shape of each object. This ensures that all entities react to the same information
and avoids coupling. 
Other notable events are signalled via an observer pattern (e.g. collisions of objects), and the gameState doubles as observer. This allows e.g. counting the total number of game-
wide collisions, and trigger changes in difficulty or color as the game progresses (independent of score). For example, the game turns cyan as soon as three collisions were detected, and 
the ball speed increases and ball color changes on every 15 collisions.
To demonstrate the versatility of the observer pattern, another observer (Sound) is added, and it plays a sound on various notable events (scores, collisions). It is independent of 
gameState and hooks directly on various Objects (paddles ball - currently the same as game state but may also be a smaller or larger subset in the future). It does not yet use sfml::sound but a simple command line output.


**Controllers and object movement:**  

The PhysicalObject class contains the current shape and can be moved around. There are in principle two forms of movement: based on physics (gravity, impulse etc), and based on 
game mechanics (control by AI, player or power items). The setDestination function of PhysicalObject is a basic setter that does not contain either, so access is restricted by making
it a protected member. The derived classes (Ball, Paddle etc) add physics via the exposed public function move(). Currently, only Ball movement is based on physics, but in the future, 
Paddles may include physics-based movement as well, e.g. impulse upon being hit by a ball, gravity etc.  
Game movement mechanics are encapsulated in a command pattern. Commands are friends with PhysicalObject, so only they are able to access the protected setter and move Paddles according
to their own logic (up or down), and ignoring physics. Usage of a command patterns separates the physical constraints of movement from those imposed by game logic.
 
Controllers fetch commands (from players or AI) and are able to return (or queue) them. Game is responsible for matching controller outputs (commands) with other objects (paddles). 
Game may have its own way of interfering with the objects as well, e.g. using commands on ball to make the ball wiggle, or on paddles to prevent them from leaving the screen. This design
allows abstract control of any object, by human, AI or the game environment without entangling the classes. Currently implemented controls are keyboard, mouse and AI.


# Isssues  
- ball jumps a bit when hitting a wall, particularly noticeable if hitting at small angles
- keybinding menu to write, possibly also menus for AI difficulty and mouse sensitivity
- if player uses mouse, paddle moves with constant speed into direction of mouse. Could instantly go to current mouse pos instead, to track the mouse more closely
- sound is missing in UML