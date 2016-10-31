// Allston Mickey - 06/03/16
// Mastermind
#ifndef mastermind_display_H_Included
#define mastermind_display_H_Included

#include <iostream>
#include <string>
#include <Windows.h>
#include "display.h"
#include "mastermind_peg.h"
#include "files.h"

void startingMenu(int winWidth, bool isCentered); // the display for the first screen when the program is run.  displays the mastermindLogo and the options to choose from, instructions, play, scores, quit
void mastermindLogo(int winWidth, bool isCentered); // ASCII art of "MASTERMIND"
void menuOptions(int winWidth); // displays "buttons" with options to choose from on startingMenu

void instructions(int winWidth, bool isCentered); // displays the instructions window
void instructionsLogo(int winWidth, bool isCentered); // ASCII art of "INSTRUCTIONS"
void instructionsMessage(); // displays the instructions

void settings(int winWidth, bool isCentered, bool allowDuplicateColors, int numberOfGuesses, int numberOfPegs); // settings window, displays before a game is played.  displays the logo and the options to choose from
void settingsLogo(int winWidth, bool isCentered); // ASCII art of "SETTINGS"
void settingsOptions(bool allowDuplicateColors, int numberOfGuesses, int numberOfPegs); // options to choose from before starting a game

void play(int winWidth, bool isCentered, mastermind_peg_H_Included::Peg *pegArry[], int numberOfTurns, int numberOfPegs, bool showCode); // play window, displays during a game.  displays the logo and the Mastermind board
void playLogo(int winWidth, bool isCentered); // ASCII art of "PLAY"
void playBoard(int winWidth, mastermind_peg_H_Included::Peg *pegArry[], int numberOfTurns, int numberOfPegs, bool showCode); // displays a Mastermind board using a multidimensional array of pegs

void scores(int winWidth, bool isCentered); // displays the scores screen
void scoresLogo(int winWidth, bool isCentered); // ASCII art of "SCORES"
void scoresList(); // displays the scores



void startingMenu(int winWidth, bool isCentered) { // the display for the first screen when the program is run.  displays the mastermindLogo and the options to choose from, instructions, play, scores, quit
	system("CLS"); // clear the screen
	mastermindLogo(winWidth, isCentered); // display the mastermind logo
	menuOptions(winWidth); // display the options to choose from
}



void mastermindLogo(int winWidth, bool isCentered) { // ASCII art of "MASTERMIND"
	std::string logoLines[5]; // array to hold each line of the logo in an index
	logoLines[0] = " __    __  ______  ______  ______  ______  ______  __    __  __  __   __  _____    ";
	logoLines[1] = "/\\ \"-./  \\/\\  __ \\/\\  ___\\/\\__  _\\/\\  ___\\/\\  == \\/\\ \"-./  \\/\\ \\/\\ \"-.\\ \\/\\  __-.  ";
	logoLines[2] = "\\ \\ \\-./\\ \\ \\  __ \\ \\___  \\/_/\\ \\/\\ \\  __\\\\ \\  __<\\ \\ \\-./\\ \\ \\ \\ \\ \\-.  \\ \\ \\/\\ \\ ";
	logoLines[3] = " \\ \\_\\ \\ \\_\\ \\_\\ \\_\\/\\_____\\ \\ \\_\\ \\ \\_____\\ \\_\\ \\_\\ \\_\\ \\ \\_\\ \\_\\ \\_\\\\\"\\_\\ \\____ - ";
	logoLines[4] = "  \\/_\/  \\/_/\\/_/\\/_/\\/_____/  \\/_/  \\/_____/\\/_/ /_/\\/_/  \\/_/\\/_/\\/_/ \\/_/\\/____/ ";

	if (isCentered) { // if the logo is to be centered,
		for (int i = 0; i < 5; i++) { // for each line of the logo,
			display_H_Included::centerStringToWindow(winWidth, logoLines[i]); // align it to the center of the window
		}
	}

	// display the centered logo
	for (int i = 0; i < 5; i++) {
		std::cout << logoLines[i] << std::endl;
	}

	std::cout << std::endl;
}



void menuOptions(int winWidth) { // displays "buttons" with options to choose from on startingMenu
	std::string alignOutputToCenter = display_H_Included::centerStringToWindow(winWidth, 79); // string of spaces required to center the follow output

	// buttons aligned to the center with instructions, play, scores, quit

	std::cout << alignOutputToCenter;
	/* top 1. */ std::cout << (char)218 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)191 << " ";
	/* top 2. */ std::cout << (char)218 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)191 << " ";
	/* top 3. */ std::cout << (char)218 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)191 << " ";
	/* top 2. */ std::cout << (char)218 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)191 << std::endl;

	std::cout << alignOutputToCenter;
	/* middle 1. */ std::cout << (char)179 << " 1. INSTRUCTIONS " << (char)179 << " ";
	/* middle 2. */ std::cout << (char)179 << "     2. PLAY     " << (char)179 << " ";
	/* middle 3. */ std::cout << (char)179 << "    3. SCORES    " << (char)179 << " ";
	/* middle 4. */ std::cout << (char)179 << "     4. QUIT     " << (char)179 << std::endl;

	std::cout << alignOutputToCenter;
	/* bottom 1. */ std::cout << (char)192 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)217 << " ";
	/* bottom 2. */ std::cout << (char)192 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)217 << " ";
	/* bottom 3. */ std::cout << (char)192 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)217 << " ";
	/* bottom 4. */ std::cout << (char)192 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)217;
}



void instructions(int winWidth, bool isCentered) { // displays the instructions window
	instructionsLogo(winWidth, isCentered); // ASCII art of "INSTRUCTIONS"
	instructionsMessage(); // displays the instructions
}



void instructionsLogo(int winWidth, bool isCentered) { // ASCII art of "INSTRUCTIONS"
	std::string logoLines[5]; // array to hold each line of the logo in an index
	logoLines[0] = " __  __   __  ______  ______  ______  __  __  ______  ______  __  ______  __   __  ______    ";
	logoLines[1] = "/\\ \\/\\ \"-.\\ \\/\\  ___\\/\\__  _\\/\\  == \\/\\ \\/\\ \\/\\  ___\\/\\__  _\\/\\ \\/\\  __ \\/\\ \"-.\\ \\/\\  ___\\   ";
	logoLines[2] = "\\ \\ \\ \\ \\-.  \\ \\___  \\/_/\\ \\/\\ \\  __<\\ \\ \\_\\ \\ \\ \\___\\/_/\\ \\/\\ \\ \\ \\ \\/\\ \\ \\ \\-.  \\ \\___  \\  ";
	logoLines[3] = " \\ \\_\\ \\_\\\\\"\\_\\/\\_____\\ \\ \\_\\ \\ \\_\\ \\_\\ \\_____\\ \\_____\\ \\ \\_\\ \\ \\_\\ \\_____\\ \\_\\\\\"\\_\\/\\_____\\ ";
	logoLines[4] = "  \\/_/\\/_/ \\/_/\\/_____/  \\/_/  \\/_/ /_/\\/_____/\\/_____/  \\/_/  \\/_/\\/_____/\\/_/ \\/_/\\/_____/ ";

	if (isCentered) { // if the logo is to be centered,
		for (int i = 0; i < 5; i++) { // for each line of the logo,
			display_H_Included::centerStringToWindow(winWidth, logoLines[i]); // align it to the center of the window
		}
	}

	// display the centered logo
	for (int i = 0; i < 5; i++) {
		std::cout << logoLines[i] << std::endl;
	}

	std::cout << std::endl;
}



void instructionsMessage() { // displays the instructions
	std::string instructionMessages[6]; // array to hold the messages
	// sets the messages for the instructions
	instructionMessages[0] = "Mastermind is a process of elimination code-breaking game.";
	instructionMessages[1] = "To win: guess the code with the correct colors and positions";
	instructionMessages[2] = "\nAfter each guess, informational pegs will be placed to the right of the board.";
	instructionMessages[3] = "Red info pegs: correct color AND position, total match";
	instructionMessages[4] = "White info pegs: correct color ONLY, incorrect position";
	instructionMessages[5] = "\nScore is determined by the amount of guesses taken.  Lower is better.";

	// displays each message
	for (int i = 0; i < 6; i++) {
		std::cout << instructionMessages[i] << std::endl;
	}
}



void settings(int winWidth, bool isCentered, bool allowDuplicateColors, int numberOfGuesses, int numberOfPegs) { // settings window, displays before a game is played.  displays the logo and the options to choose from
	settingsLogo(winWidth, isCentered); // ASCII art of "SETTINGS"
	settingsOptions(allowDuplicateColors, numberOfGuesses, numberOfPegs);
}



void settingsLogo(int winWidth, bool isCentered) {
	std::string logoLines[5]; // array to hold each line of the logo in an index
	logoLines[0] = " ______  ______  ______  ______  __  __   __  ______  ______    ";
	logoLines[1] = "/\\  ___\\/\\  ___\\/\\__  _\\/\\__  _\\/\\ \\/\\ \"-.\\ \\/\\  ___\\/\\  ___\\   ";
	logoLines[2] = "\\ \\___  \\ \\  __\\\\/_/\\ \\/\\/_/\\ \\/\\ \\ \\ \\ \\-.  \\ \\ \\__ \\ \\___  \\  ";
	logoLines[3] = " \\/\\_____\\ \\_____\\ \\ \\_\\   \\ \\_\\ \\ \\_\\ \\_\\\\\"\\_\\ \\_____\\/\\_____\\ ";
	logoLines[4] = "  \\/_____/\\/_____/  \\/_/    \\/_/  \\/_/\\/_/ \\/_/\\/_____/\\/_____/ ";

	if (isCentered) { // if the logo is to be centered,
		for (int i = 0; i < 5; i++) { // for each line of the logo,
			display_H_Included::centerStringToWindow(winWidth, logoLines[i]); // align it to the center of the window
		}
	}

	// display the centered logo
	for (int i = 0; i < 5; i++) {
		std::cout << logoLines[i] << std::endl;
	}

	std::cout << std::endl;
}



void settingsOptions(bool allowDuplicateColors, int numberOfGuesses, int numberOfPegs) { // options to choose from before starting a game
	std::cout << "1. Allow Duplicate Colors ";
	if (allowDuplicateColors) { // if the user wants to allow duplicate colors
		std::cout << "[" << (char)251 << "]" << std::endl; // display a check mark/square root
	}
	else if (!allowDuplicateColors) { // if the user doesn't want to allow duplicate colors
		std::cout << "[X]" << std::endl; // display an X
	}

	std::cout << "2. Number of guesses (min of 1, max of 9): " << numberOfGuesses << std::endl; // display the number of guesses
	std::cout << "3. Number of pegs (min of 1, max of 5): " << numberOfPegs << std::endl; // display the number of pegs
	std::cout << "4. Finish settings and play" << std::endl; // display finish the settings
}



void play(int winWidth, bool isCentered, mastermind_peg_H_Included::Peg *pegArry[], int numberOfTurns, int numberOfPegs, bool showCode) { // play window, displays during a game.  displays the logo and the Mastermind board
	playLogo(winWidth, isCentered); // ASCII art of "PLAY"
	playBoard(winWidth, pegArry, numberOfTurns, numberOfPegs, showCode); // displays a Mastermind board using a multidimensional array of pegs
}



void playLogo(int winWidth, bool isCentered) { // ASCII art of "PLAY"
	std::string logoLines[5]; // array to hold each line of the logo in an index
	logoLines[0] = " ______  __      ______  __  __    ";
	logoLines[1] = "/\\  == \\/\\ \\    /\\  __ \\/\\ \\_\\ \\   ";
	logoLines[2] = "\\ \\  _-/\\ \\ \\___\\ \\  __ \\ \\____ \\  ";
	logoLines[3] = " \\ \\_\\   \\ \\_____\\ \\_\\ \\_\\/\\_____\\ ";
	logoLines[4] = "  \\/_/    \\/_____/\\/_/\\/_/\\/_____/ ";

	if (isCentered) { // if the logo is to be centered,
		for (int i = 0; i < 5; i++) { // for each line of the logo,
			display_H_Included::centerStringToWindow(winWidth, logoLines[i]); // align it to the center of the window
		}
	}

	// display the centered logo
	for (int i = 0; i < 5; i++) {
		std::cout << logoLines[i] << std::endl;
	}

	std::cout << std::endl;
}



void playBoard(int winWidth, mastermind_peg_H_Included::Peg *pegArry[], int numberOfTurns, int numberOfPegs, bool showCode) { // displays a Mastermind board using a multidimensional array of pegs
	std::string alignOutputToCenter = centerStringToWindow(winWidth, (2 * numberOfPegs) + (2 * (numberOfPegs - 1)) + 5); // string of spaces that aligns the board to the middle of the screen
	for (int i = 0; i < numberOfTurns + 1; i++) { // for each turn (+1 for the code)
		std::cout << alignOutputToCenter; // align the board to the center
		for (int j = 0; j < 2 * numberOfPegs; j++) { // for each guess peg and info peg
			if (j == 0) {
				display_H_Included::setConsoleColor(COLORS::gray, COLORS::gray); // sets the console color to the background color of the board
				std::cout << " "; // add a space for the left border of the board
			}
			if (j == numberOfPegs) { //if there is an info peg about to be placed, seperate it from the guess pegs with a lot of spaces
				std::cout << "   "; // seperate the pegs with a space
			}
			if (i == 0) {  // if the peg is a code peg (in the code peg row?)
				if (j < numberOfPegs) { // if the peg isn't an info peg
					if (showCode) { // if the code is being shown,
						pegArry[i][j].display(COLORS::gray); std::cout << " "; // display the code peg
					}
					else { // if the code is being hidden
						// display a black question mark
						display_H_Included::setConsoleColor(COLORS::black, COLORS::gray);
						std::cout << "?" << " ";
					}
				}
				else { // if the peg is an info peg
					pegArry[i][j].display(COLORS::gray); std::cout << " "; // display a gray peg (blends into the background so it looks like nothing is there, no info pegs for the code!)
				}
			}
			else { // if the peg is not an info peg
				pegArry[i][j].display(COLORS::gray); std::cout << " "; // display the peg as gray
			}
		}
		display_H_Included::setConsoleColor(COLORS::lightGray); // change the console color back to default
		std::cout << std::endl;
	}
	std::cout << std::endl;
}



void scores(int winWidth, bool isCentered) { // displays the scores screen
	scoresLogo(winWidth, isCentered); // ASCII art of "SCORES"
	scoresList(); // displays the scores
}



void scoresLogo(int winWidth, bool isCentered) { // ASCII art of "SCORES"
	std::string logoLines[5]; // array to hold each line of the logo in an index
	logoLines[0] = " ______  ______  ______  ______  ______  ______    ";
	logoLines[1] = "/\\  ___\\/\\  ___\\/\\  __ \\/\\  == \\/\\  ___\\/\\  ___\\   ";
	logoLines[2] = "\\ \\___  \\ \\ \\___\\ \\ \\/\\ \\ \\  __<\\ \\  __\\\\ \\___  \\  ";
	logoLines[3] = " \\/\\_____\\ \\_____\\ \\_____\\ \\_\\ \\_\\ \\_____\\/\\_____\\ ";
	logoLines[4] = "  \\/_____/\\/_____/\\/_____/\\/_/ /_/\\/_____/\\/_____/ ";

	if (isCentered) { // if the logo is to be centered,
		for (int i = 0; i < 5; i++) { // for each line of the logo,
			display_H_Included::centerStringToWindow(winWidth, logoLines[i]); // align it to the center of the window
		}
	}

	// display the centered logo
	for (int i = 0; i < 5; i++) {
		std::cout << logoLines[i] << std::endl;
	}

	std::cout << std::endl;
}



void scoresList() { // displays the scores
	std::ifstream scoresData("scores.dat");
	if (!scoresData.is_open()) { // if the load/save file doesn't exist
		std::ofstream newScoreData("scores.dat"); // create it
	}

	char delim = ';'; // delimiter character signifying a break between words while parsing
	readFile(scoresData, "scores.dat"); // reopen the file
	int scoresArryLength = files_H_Included::countWords(scoresData, delim);
	if (scoresArryLength > -1) { // if a score exists
		std::string *scoresArry = new std::string[scoresArryLength]; // create an array to hold the scores
		readFile(scoresData, "scores.dat"); // reopen the file
		files_H_Included::parseWords(scoresData, scoresArry, delim); // read the file of scores, store each score in scoresArry
		// display each score
		for (int i = 0; i < scoresArryLength; i++) {
			std::cout << i + 1 << ". " << scoresArry[i] << std::endl;
		}
	}
	else { // if the are no scores yet
		std::cout << "No scores yet!  Go win!" << std::endl; // display a message telling them to get a score
	}
}
#endif
