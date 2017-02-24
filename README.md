# AI-Problem-Solver
---
A library for solving problems using AI methods. Originally made for assignments in COMP 4106 at Carleton University. There are two types of problems of interest in this project:

#### 1. Puzzles
The goal is to find some solution state which meets certain requirements. Puzzles are solved by one agent in isolation (i.e., the state is not changing in between moves and there is no competing agent). In most puzzles, the steps to reach this state are also part of the solution.

##### Included puzzles
###### Bridge puzzle
A number of people must move over a narrow bridge at night. The bridge can only hold two people at a time and a torch has to be used to cross the bridge. Each person takes a certain amount of time to cross the bridge. When two people are crossing the bridge together, they both move at the pace dictated by the slower person. The task is get the group across the bridge in the minimum time.

###### Tile puzzle
An mxn grid contains tiles with the numbers 1 through (mxn)-1 on them. Initially these tiles are in a random order. One space is left blank (tile number = 0). The goal is to arrange the tiles in the correct order (ascending in value from left to right, top to bottom - the blank tile goes in the bottom rightmost position). Any tile that is adjacent or diagonal to the blank space can slide into it and two non-blank tiles can be swapped as per the chess knight move (L shape).

#### 2. Games
The goal is to beat an opponent in reaching some winning state. There *is* a competing agent actively working against you. Here, there is no solution - only moves that are better or worse than that of the opponent.

##### Included games
###### Focus / Domination
A board game played on a grid. Pieces can be stacked on top of each other. A player is said to control a stack if one of their pieces is topmost. On a player's turn, they can move a stack they control vertically or horizontally any number of grid cells up to the number of pieces being moved. When a stack is moved on top of another and the new height is greater than 5, the lower pieces are captured by the player who made the move. Each player starts with 18 pieces randomly placed in the inner 6x6 square of the board. The game ends when one player, the loser, has no more valid moves (i.e., the other player controls all of the stacks).

Note that this game is modified from the original 1964 version: players may choose to move only the top 3 pieces of a stack of height 5 on their turn, the "self capture" rule is not implemented, and the game can end early if one player captures 8 or more of the opponent's pieces. See https://en.wikipedia.org/wiki/Focus_(board_game) for the original rules.


### Calling the library
#### Puzzles
Simply create an instance of the appropriate `AI::Puzzle` derived class for the puzzle to solve, passing in the desired `AI::SearchType` (i.e., `AI::BREADTH_FIRST`, `AI::DEPTH_FIRST`, or `AI::A_STAR`), and call `AI::Puzzle::solve()`. The results will be printed to stdout.

#### Games
Simply create an instance of the appropriate `AI::Game` derived class for the game to play, passing in the `searchDepth` parameter for the AI player(s), and call `AI::Game::play()`. Gameplay output will depend on the game's implementation (e.g., the included Focus example pits 2 AI players against each other).


### Solving a new problem
Several abstract classes are given in `LibAI`. In order to solve a new problem, the following classes must be extended. The `AI::Util::getInt` function can be used to easily get numeric user input (see the included examples).

#### `AI::State`
A state in the state space of the problem. Override the following methods for your problem.

`unsigned long AI::State::getStateCode() const`
* Should return a hash value for the state (used when looking up states and doing comparisons)

`void AI::State::getActions(std::vector<AI::Action*>& actions) const`
* Should populate `actions` with the set of (dynamically allocated) `AI::Action`s that can be applied to the state

`std::string AI::State::describe() const`
* Should return a string representation of the state (used for the UI)

`int AI::State::heuristicValue() const`
* Heuristic function, used for A* search when solving puzzles (should return the estimated distance to the goal state) and MiniMax when playing games (should return the utility value of the state).

#### `AI::Action`
An action that can be performed on an `AI::State`. Override the following methods for your problem.

`int AI::Action::execute(const AI::State* inState, AI::State** outState)`
* Should apply, dynamically allocate, and return the result of applying the action to `inState` through `outState`
* Should return a value indicating the cost of the action

`std::string AI::Action::describe(const AI::State* s=NULL)`
* Should return a string representation of the action (used for the UI)
* The state the action will be applied to will be passed as the `s` argument (sometimes needed to describe the action)

#### `AI::Puzzle` (if the problem is a puzzle)
A puzzle that can be solved using AI techniques. Override the following methods for your puzzle.

`AI::State* AI::Puzzle::genInitialState()`
* Should return the (dynamically allocated) initial state of the puzzle

`AI::State* AI::Puzzle::genGoalState()`
* Should return the (dynamically allocated) goal state of the puzzle

#### `AI::Game` (if the problem is a game)
A game that can be solved using AI techniques. Override the following methods for your game.

`bool AI::Game::gameEnded(const AI::State* state) const`
* Should return true if the game is over for `state`

`void AI::Game::play() const`
* Should implement the game loop. Typically, this is:
    * Display the current state
    * Get the next `AI::Action` and `AI::State` by calling `AI::Game::nextMove`
    * Update variables accordingly (i.e., the "current state" variable)
* Player switching and user input (if the game is interactive) should go here as well
* See the included Focus example for more. It is implemented as AI versus AI, where each player uses a different heuristic
