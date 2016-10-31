// Allston Mickey - 06/03/16
// Mastermind
#ifndef mastermind_peg_H_Included
#define mastermind_peg_H_Included

#include <iostream>
#include <string>
#include "display.h"

/*  Peg states are put into 4 categories;
0. inactive - the peg isn't on the board yet/default
1. code - a peg that is part of the secret code being guessed
2.	guess - a peg that is used to guess the code
3.	info - the "side" pegs, indicates a. if a guess is a. the right color and position, or b. the right color and incorrect position
*/
enum STATES_PEGS {
	inactive = 0,
	code = 1,
	guess = 2,
	info = 3,
};

enum COLORS {
	black = 0,
	darkBlue = 1,
	darkGreen = 2,
	darkCyan = 3,
	darkRed = 4,
	darkPink = 5,
	darkYellow = 6,
	lightGray = 7,
	gray = 8,
	blue = 9,
	green = 10,
	cyan = 11,
	red = 12,
	pink = 13,
	yellow = 14,
	white = 15
};

/*	COLOR OF PEGS:
background of console (the board) is gray
current row with no pegs: darkBlue
inactive: lightGray
black is reserved for inactive info pegs
red is reserved for info pegs (matching color and position)
white is reserved for info pegs (matching color only)
*/
enum COLORS_PEGS {
	peg1 = COLORS::blue,
	peg2 = COLORS::cyan,
	peg3 = COLORS::green,
	peg4 = COLORS::pink,
	peg5 = COLORS::yellow,
	pegInactive = COLORS::lightGray,
	pegGuessDefault = COLORS::darkBlue,
	pegInfoDefault = COLORS::black,
	pegInfoColorAndPositionMatch = COLORS::red,
	pegInfoColorOnlyMatch = COLORS::white
};


class Peg {
public: // constructors
	Peg() { set(STATES_PEGS::inactive, COLORS_PEGS::pegInfoDefault, 0); } // default peg of an inactive state and a default info color, turn 0
	Peg(int state) { set(state, COLORS_PEGS::pegInfoDefault, 0); } // peg of a specified state and a default info color, turn 0
	Peg(int state, int color) { set(state, color, 0); } // peg of a specified state and color, turn 0
	Peg(int state, int color, int turn) { set(state, color, turn); } // peg of specified state, color, and turn
private:
	int state_; // is it inactive (0)?  the code (1)?  a guess (2)?  a side peg (3)?
	int color_; // the color of the peg
	int turn_; // the turn number the the peg is being used on, '0' for not used yet or code peg
public:
	// gets the ___ of the peg
	// sets the ___ of the peg
	int getState() { return state_; }
	int getColor() { return color_; }
	int getTurn() { return turn_; }
	void setState(int state) { state_ = state; }
	void setColor(int color) { color_ = color; }
	void setTurn(int turn) { turn_ = turn; }
	void set(int state, int color, int turn) { setState(state); setColor(color); setTurn(turn); } // sets all attributes of a peg at once

	void display(int backgroundColor) { // display the peg with it's specified color (foreground) and a background color
		display_H_Included::setConsoleColor(getColor(), backgroundColor);
		std::cout << (char)254;
	}
};
#endif
