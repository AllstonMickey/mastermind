/*
 * Author: Allston Mickey
 * Date: 06/03/16
 * Windows console simulation of the board game "Mastermind".
 */
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>
#include <time.h>
#include <cstdlib>
#include "display.h"
#include "input.h"
#include "files.h"
#include "mastermind_display.h"
#include "mastermind_peg.h"

enum STATES_GAME { // if the game is still going on, lost, or won
	won = 2,
	lost = 1,
	ongoing = 0
};

// generic functions
bool isElementAlreadyInArray(int arry[], int arryLength, int element); // checks if an element is already in an array
int randomNumGen(int range, int initial); // returns a "random" number
void bubbleSort(int arry[], int len); // sorts an int array from smallest at the 0th index to largest at the len-1 index

// game functions
bool duplicatePegsExist(mastermind_peg_H_Included::Peg *pegArry[], int numberOfPegs, int numberOfTurns, int currentTurn); // checks if duplicate pegs exist in the user's guess
bool guessPegsMatchCode(mastermind_peg_H_Included::Peg *pegArry[], int numberOfPegs, int numberOfTurns, int currentTurn); // checks if if the pegs in the user's guess match the code
bool pegsAreChangedFromDefault(mastermind_peg_H_Included::Peg *pegArry[], int numberOfPegs, int numberOfTurns, int currentTurn); // checks if the pegs have been changed from the default dark blue color and inactive state
int determineGameState(mastermind_peg_H_Included::Peg *pegArry[], int numberOfPegs, int numberOfTurns, int currentTurn); // checks if the user has won, lost, or the game is still being played out
std::string getInitials(); // get 3 letters ("initials") from the user
void addNewScore(int currentTurn, std::string initials, bool allowDuplicateColors, int numberOfPegs, int numberOfTurns); // adds a new score to the score.dat file and resorts the scores from best being first, to worst being last
void createCode(mastermind_peg_H_Included::Peg *pegArry[], bool allowDuplicateColors, int numberOfPegs); // generate the secret code
void displayAvailablePegs(); // displays the pegs for the user to choose from in their guess
void displayPegGuessOptions(int selectedColor, int selectedSlot); // displays the options for the user to choose from when playing the game (choosing peg color and slot, placing the peg, finishing the turn)
void displayPegsMDArry(mastermind_peg_H_Included::Peg *pegArry[], int numberOfTurns, int numberOfPegs); // displays the board of pegs as a matrix for testing purposes
void endOfRound(mastermind_peg_H_Included::Peg *pegArry[], int numberOfPegs, int numberOfTurns, int &currentTurn, bool &continueGame, int winWidth, bool isCentered, bool allowDuplicateColors); // differs from finishTurn in that endOfRound only executes after finishTurn and when a turn has been completed successfully, while finishTurn executes in every scenario (ex: if the user makes a mistake in the input)
void executeMenuOption(int optionToExec, bool &continueProgram, int winWidth, bool isCentered); // do what option was chosen in setMenuOption
void finishTurn(mastermind_peg_H_Included::Peg *pegArry[], int numberOfPegs, int numberOfTurns, int &currentTurn, bool allowDuplicateColors, bool &continueGame, int winWidth, bool isCentered); // when the user chooses to end a turn, this always executes.  checks if there are any errors in the user's guess, if so, doesn't move forward to the next turn.  if not, executes endOfRound
void playChangePegColor(int &pegColor); // changes the peg color while playing the game
void playChangePegSlot(int &pegSlot, int numberOfPegs); // changes the peg slot while playing the game
void playTheGame(int winWidth, bool isCentered); // from the main menu, executes the settings menu and eventually the game
void populateBoard(mastermind_peg_H_Included::Peg *pegArry[], int numberOfTurns, int numberOfPegs, bool allowDuplicateColors); // populates the board of pegs, determined by how many turns and pegs the user chose
void setInfoPegs(mastermind_peg_H_Included::Peg *pegArry[], int numberOfPegs, int numberOfTurns, int currentTurn); // sets the info pegs (the pegs on the far right side of the board)
void setMenuOption(int &menuOption); // sets an option from the main menu (1 instructions, 2 play, 3 scores, 4 quit)
void setPegOptions(mastermind_peg_H_Included::Peg *pegArry[], int &pegColor, int &pegSlot, int numberOfPegs, int numberOfTurns, int &currentTurn, bool allowDuplicateColors, bool &continueGame, int winWidth, bool isCentered); // followup of displayPegGuessOptions.  executes the chosen option (changing peg color & slot, placing the peg, ending the turn)
void setSettingsOption(bool &changingSettings, bool &allowDuplicateColors, int &numberOfTurns, int &numberOfPegs); // sets the settings for the game
void settingsWindow(int winWidth, bool isCentered, bool &allowDuplicateColors, int &numberOfTurns, int &numberOfPegs); // holds all of the code for the settings window before starting a game
void sortScores(std::string scoresArry[], int scoresLength); // sorts scores from best at the 0th index to worst at the scoresLength-1 index





int main() {
	srand(time(NULL)); // seed the time from the system

	bool isDisplayInCenter = true, useProgram = true; // the display is centered if given the option, the user is using the program
	int selectedResolution = 0, resolutionWidths[3], resolutionHeights[3], userMenuOption; // declares the resolutions and initializes which resolution to use.  userMenuOption is the main menu option that the user wishes to use (instructions, play, scores, quit)
	display_H_Included::populateResolutionsArray(resolutionWidths, resolutionHeights); // populates/initializes the resolutions array
	display_H_Included::resizeWindow(resolutionWidths, resolutionHeights); // works on any windows version.  resizes the console window based on the amount of columns and lines

	while (useProgram) { // while using the program
		mastermind_display_H_Included::startingMenu(resolutionWidths[selectedResolution], isDisplayInCenter); // display the starting menu
		setMenuOption(userMenuOption); // set the menu option (instructions, play, scores, quit)
		executeMenuOption(userMenuOption, useProgram, resolutionWidths[selectedResolution], isDisplayInCenter); // execute the specified menu option
	}

	std::cout << "\nGoodbye!  Closing on next keypress . . ."; // goodbye message
	system("PAUSE>NUL"); // pause the program without a message
	return 0; // end the program
}




// generic functions
bool isElementAlreadyInArray(int arry[], int arryLength, int element) { // checks if an element is already in an array
	for (int i = 0; i < arryLength; i++) {
		if (arry[i] == element)
			return true;
	}
	return false;
}



int randomNumGen(int range, int initial) { // returns a random number
	int randomNumber = rand() % range + initial; // get a random number between a range that starts at some initial value
	return randomNumber; // return that random number
}



void bubbleSort(int arry[], int len) { // sorts an int array from smallest at the 0th index to largest at the len-1 index
	bool swapped = true;
	int j = 0;
	int temp;
	while (swapped) {
		swapped = false;
		j++;
		for (int i = 0; i < len - j; i++) {
			if (arry[i] > arry[i + 1]) {
				temp = arry[i];
				arry[i] = arry[i + 1];
				arry[i + 1] = temp;
				swapped = true;
			}
		}
	}
}



// game functions
bool duplicatePegsExist(mastermind_peg_H_Included::Peg *pegArry[], int numberOfPegs, int numberOfTurns, int currentTurn) { // checks if duplicate pegs exist in the user's guess
	// sort the colors and
	int *guessedPegs = new int[numberOfPegs];
	for (int i = 0; i < numberOfPegs; i++) {
		guessedPegs[i] = pegArry[numberOfTurns - currentTurn][i].getColor();
	}
	bubbleSort(guessedPegs, numberOfPegs);

	// if they ever equal return true, duplicate pegs do exist
	for (int i = 1; i < numberOfPegs; i++) {
		if (guessedPegs[i - 1] == guessedPegs[i]) {
			return true;
		}
	}
	return false; // return false, duplicate color pegs do not exist
}



bool guessPegsMatchCode(mastermind_peg_H_Included::Peg *pegArry[], int numberOfPegs, int numberOfTurns, int currentTurn) { // checks if if the pegs in the user's guess match the code
	for (int i = numberOfPegs; i < 2 * numberOfPegs; i++) { // for each info peg
		if (pegArry[numberOfTurns - currentTurn][i].getColor() != COLORS_PEGS::pegInfoColorAndPositionMatch) { // if the info peg does is not a matching color and position peg (red peg)
			return false; // then the guess does not match the code
		}
	}
	return true; // the guess matches the code
}



bool pegsAreChangedFromDefault(mastermind_peg_H_Included::Peg *pegArry[], int numberOfPegs, int numberOfTurns, int currentTurn) { // checks if the pegs have been changed from the default dark blue color and inactive state
	for (int i = 0; i < numberOfPegs; i++) { // for each guess peg
		if (pegArry[numberOfTurns - currentTurn][i].getState() != STATES_PEGS::guess) { // if the state isn't a guess (then it hasn't been placed!)
			return false; // return false, the pegs have not been placed/changed from default
		}
	}
	return true; // if you've gotten this far then the pegs have been placed and changed from default, continue.
}



int determineGameState(mastermind_peg_H_Included::Peg *pegArry[], int numberOfPegs, int numberOfTurns, int currentTurn) { // checks if the user has won, lost, or the game is still being played out
	if (numberOfTurns - currentTurn - 1 == 0) { // if the user has used every guess/turn, determine if they lost or won
		if (guessPegsMatchCode(pegArry, numberOfPegs, numberOfTurns, currentTurn)) { // if the last info peg is red (color and position match the code) then all of the other info pegs must be too, the user has won
			return won; // return won/2
		}
		else { // if the info pegs are not all red (all of the guess pegs don't match the code), the user has lost
			return lost; // return lost/1
		}
	}
	else {
		if (guessPegsMatchCode(pegArry, numberOfPegs, numberOfTurns, currentTurn)) { // if the last info peg is red (color and position match the code) then all of the other info pegs must be too, the user has won
			return won; // return won/2
		}
		else { // if the info pegs are not all red (all of the guess pegs don't match the code), the user has lost
			return ongoing; // return 0/ongoing
		}
	}
}



std::string getInitials() { // get 3 letters ("initials") from the user
	std::string initials; // string to hold the initials
	std::cin >> initials;
	while (initials.length() > 3 || !input_H_Included::isLetters(initials)) { // while the initials are longer than three characters or are not letters
																			  // tell the user, depending on what was wrong...
		if (initials.length() > 3) { // too long of an input
			std::cout << "The length of your initials must be three or less characters." << std::endl;
		}
		if (!input_H_Included::isLetters(initials)) { // input contained non-letters
			std::cout << "The initials must contain letters only." << std::endl;
		}
		std::cout << "Enter your initials again: "; // ask for their initials again
		std::cin >> initials; // get their initials
	}
	return initials; // return their valid initials
}



void addNewScore(int currentTurn, std::string initials, bool allowDuplicateColors, int numberOfPegs, int numberOfTurns) { // adds a new score to the score.dat file and resorts the scores from best being first, to worst being last
	std::ifstream scoresData("scores.dat");
	if (!scoresData.is_open()) { // if the load/save file doesn't exist
		std::ofstream newScoreData("scores.dat"); // create it
	}

	char delim = ';';
	files_H_Included::readFile(scoresData, "scores.dat");
	int numberOfPreviousScores = files_H_Included::countWords(scoresData, delim); // count the number of scores currently in the file
	int scoresArryLength;
	if (numberOfPreviousScores == -1) { // if there are no scores
		scoresArryLength = 1; // the number of new scores is 1, the one just created
	}
	else { // if there are scores
		scoresArryLength = numberOfPreviousScores + 1; // then the number of new scores is the previous + the one just created
	}

	std::string *scoresArry = new std::string[scoresArryLength]; // create an array holding the scores
	files_H_Included::readFile(scoresData, "scores.dat"); // reopen the file
	files_H_Included::parseWords(scoresData, scoresArry, delim); // parse the scores in the file (adds the scores to scoresArry)

																 // put the score just created into the scores array
	scoresArry[scoresArryLength - 1] = '[' + input_H_Included::intToStr(currentTurn) + ' ' + initials + "]    settings: ";
	if (allowDuplicateColors) {
		scoresArry[scoresArryLength - 1] += "yes ";
	}
	else {
		scoresArry[scoresArryLength - 1] += "no ";
	}
	scoresArry[scoresArryLength - 1] += "duplicates, " + input_H_Included::intToStr(numberOfPegs) + " pegs, " + input_H_Included::intToStr(numberOfTurns) + " turns";
	std::string newScore = scoresArry[scoresArryLength - 1]; // string to hold the new score, used to check later if it's a high score
	sortScores(scoresArry, scoresArryLength); // sort the scores from best in the 0th index (score closest to 0) to worst in the nth index (score closest to 9)

	if (newScore == scoresArry[0]) { // if the new score is the best score
		std::cout << "New high score!" << std::endl; // there is a high score, tell the user
	}

	// output each score to the file, seperated by the delimiter
	std::ofstream updatedScoreData("scores.dat");
	for (int i = 0; i < scoresArryLength; i++) {
		updatedScoreData << scoresArry[i] << ';';
	}
}



void createCode(mastermind_peg_H_Included::Peg *pegArry[], bool allowDuplicateColors, int numberOfPegs) { // generate the secret code
	int availableColors[5] = { COLORS_PEGS::peg1, COLORS_PEGS::peg2, COLORS_PEGS::peg3, COLORS_PEGS::peg4, COLORS_PEGS::peg5 }; // colors to choose from

	if (allowDuplicateColors) { // if the user wants duplicate colors
		for (int i = 0; i < numberOfPegs; i++) { // for each peg
			pegArry[0][i].setColor(availableColors[randomNumGen(5, 0)]); // set the color of the code peg to a random color (number)
		}
	}
	else if (!allowDuplicateColors) { // if the user DOES NOT want duplicate colors
		int chosenColors[5]; // array to hold the colors that have been chosen
		for (int i = 0; i < numberOfPegs; i++) { // for each peg
			int randNum;
			do {
				randNum = randomNumGen(6, 0); // generate a random number (color)
			} while (isElementAlreadyInArray(chosenColors, 5, availableColors[randNum])); // while the random number (color) is already chosen
			chosenColors[i] = availableColors[randNum]; // the color has been chosen, add it to the chosen array to signify that
			pegArry[0][i].setColor(availableColors[randNum]); // set the color of the code peg to the random color (number)
		}
	}
}



void displayAvailablePegs() { // displays the pegs for the user to choose from in their guess
	std::cout << "\nPegs to choose from: ";
	display_H_Included::setConsoleColor(COLORS_PEGS::peg1); std::cout << " 1. " << (char)254 << "   ";
	display_H_Included::setConsoleColor(COLORS_PEGS::peg2); std::cout << "2. " << (char)254 << "   ";
	display_H_Included::setConsoleColor(COLORS_PEGS::peg3); std::cout << "3. " << (char)254 << "   ";
	display_H_Included::setConsoleColor(COLORS_PEGS::peg4); std::cout << "4. " << (char)254 << "   ";
	display_H_Included::setConsoleColor(COLORS_PEGS::peg5); std::cout << "5. " << (char)254 << " ";
	display_H_Included::setConsoleColor(COLORS::lightGray);
	std::cout << std::endl;
}



void displayPegGuessOptions(int selectedColor, int selectedSlot) { // displays the options for the user to choose from when playing the game (choosing peg color and slot, placing the peg, finishing the turn)
																   // displays the current peg
	std::cout << "\n1. Select a peg color (current: ";
	display_H_Included::setConsoleColor(selectedColor); std::cout << (char)254;
	display_H_Included::setConsoleColor(COLORS::lightGray); std::cout << ")" << std::endl;

	std::cout << "2. Select a slot to put the current peg in (current: " << selectedSlot + 1 << ")" << std::endl; // display the current slot
	std::cout << "3. Place peg" << std::endl; // place a peg
	std::cout << "4. Finish turn" << std::endl; // finish a turn
}



void displayPegsMDArry(mastermind_peg_H_Included::Peg *pegArry[], int numberOfTurns, int numberOfPegs) { // displays the board of pegs as a matrix for testing purposes
	for (int i = 0; i < numberOfTurns + 1; i++) { // for each turn (+1 for code)
		for (int j = 0; j < 2 * numberOfPegs; j++) { // for each guess peg and info peg
			std::cout << "pegs[" << i << "][" << j << "]: " << pegArry[i][j].getState() << ", " << pegArry[i][j].getColor() << ", " << pegArry[i][j].getTurn() << std::endl; // display the peg row, column, state, color, and turn
		}
	}
}



void endOfRound(mastermind_peg_H_Included::Peg *pegArry[], int numberOfPegs, int numberOfTurns, int &currentTurn, bool &continueGame, int winWidth, bool isCentered, bool allowDuplicateColors) { // differs from finishTurn in that endOfRound only executes after finishTurn and when a turn has been completed successfully, while finishTurn executes in every scenario (ex: if the user makes a mistake in the input)
	setInfoPegs(pegArry, numberOfPegs, numberOfTurns, currentTurn); // set the info pegs for the current guess
	int gameState = determineGameState(pegArry, numberOfPegs, numberOfTurns, currentTurn); // determine the state of the game
	if (gameState == won || gameState == lost) { // if the user has won or lost
		system("CLS"); // clear the screen
		mastermind_display_H_Included::play(winWidth, isCentered, pegArry, numberOfTurns, numberOfPegs, true); // display the code
		std::string endGameMessage; // hold the end message
		if (gameState == won) { // if the user won
			endGameMessage = "You won!";
			std::cout << display_H_Included::centerStringToWindow(winWidth, endGameMessage.length()) << endGameMessage << std::endl; // display that they won
			std::cout << "Your score: " << currentTurn << std::endl; // display their score/number of guesses
			std::cout << "Your initials (3): "; // ask for their initials
			std::string newScoreInitials = getInitials(); // get their initials
			addNewScore(currentTurn, newScoreInitials, allowDuplicateColors, numberOfPegs, numberOfTurns); // add their score to the file containing all scores, check for a high score
		}
		else { // if the user lost
			endGameMessage = "You lost.  The code is now shown.";
			std::cout << display_H_Included::centerStringToWindow(winWidth, endGameMessage.length()) << endGameMessage << std::endl; // display that they lost
			std::cout << display_H_Included::centerStringToWindow(winWidth, 13) << "Your score: " << currentTurn << std::endl; // display their score
		}
		continueGame = false; // the game has ended
	}
	else { // if the game is still being played (gameState == ongoing)
		currentTurn++; // go onto the next turn
		for (int i = 0; i < numberOfPegs; i++) { // for each guess peg
			pegArry[numberOfTurns - currentTurn][i].setColor(COLORS_PEGS::pegGuessDefault); // set the color of the pegs to the guess default, showing that they are the ones being selected
		}
	}
}



void executeMenuOption(int optionToExec, bool &continueProgram, int winWidth, bool isCentered) { // do what option was chosen in setMenuOption
	if (optionToExec == 1) { // display instructions
		system("CLS");
		mastermind_display_H_Included::instructions(winWidth, isCentered);
		std::cout << "\nContinuing to main menu on next keypress . . .";
		system("PAUSE>NUL");
	}
	else if (optionToExec == 2) { // play the game
		playTheGame(winWidth, isCentered);
	}
	else if (optionToExec == 3) { // display scores
		system("CLS");
		mastermind_display_H_Included::scores(winWidth, isCentered);
		std::cout << "\nContinuing to main menu on next keypress . . .";
		system("PAUSE>NUL");
	}
	else if (optionToExec == 4) { // quit the program
		continueProgram = false;
	}
}



void finishTurn(mastermind_peg_H_Included::Peg *pegArry[], int numberOfPegs, int numberOfTurns, int &currentTurn, bool allowDuplicateColors, bool &continueGame, int winWidth, bool isCentered) { // when the user chooses to end a turn, this always executes.  checks if there are any errors in the user's guess, if so, doesn't move forward to the next turn.  if not, executes endOfRound
	if (pegsAreChangedFromDefault(pegArry, numberOfPegs, numberOfTurns, currentTurn)) { // if the pegs are changed from the default then continue
		if (allowDuplicateColors) { // if the user allows duplicate colors in the code (and guess)
			endOfRound(pegArry, numberOfPegs, numberOfTurns, currentTurn, continueGame, winWidth, isCentered, allowDuplicateColors); // then check the info pegs and update the game state
		}
		else if (!allowDuplicateColors) { // if the user doesn't allow duplicate colors in the code (and guess)
			if (!duplicatePegsExist(pegArry, numberOfPegs, numberOfTurns, currentTurn)) { // if duplicate pegs don't exist
				endOfRound(pegArry, numberOfPegs, numberOfTurns, currentTurn, continueGame, winWidth, isCentered, allowDuplicateColors); // then check the info pegs and update the game state
			}
			else { // if duplicate pegs exist (when they shouldn't)
				std::cout << "You made a guess with duplicate pegs but you turned that option off.\nFix your guess and try again.  Continuing on keypress . . ."; // tell the user that they have duplicates
				system("PAUSE>NUL");
			}
		}
	}
	else { // if the pegs are not changed from the default then tell the user
		std::cout << "You must change all pegs to a color (not the default dark blue).  Try again." << std::endl; // tell the user that they must place pegs to finish a turn
		std::cout << "Continuing on keypress . . ." << std::endl;
		system("PAUSE>NUL");
	}
}



void playChangePegColor(int &pegColor) {  // changes the peg color while playing the game
	std::cout << "Enter one of the above peg colors: ";
	// get a valid peg color
	int temp = input_H_Included::getInteger();
	while (temp < 1 || temp > 5) {
		std::cout << "You must enter '1', '2', '3', '4', or '5': ";
		temp = input_H_Included::getInteger();
	}
	pegColor = temp;
	switch (pegColor) { // depending on the peg color selected, set the peg color to that
	case 1:
		pegColor = COLORS_PEGS::peg1;
		break;
	case 2:
		pegColor = COLORS_PEGS::peg2;
		break;
	case 3:
		pegColor = COLORS_PEGS::peg3;
		break;
	case 4:
		pegColor = COLORS_PEGS::peg4;
		break;
	case 5:
		pegColor = COLORS_PEGS::peg5;
		break;
	}
}



void playChangePegSlot(int &pegSlot, int numberOfPegs) { // changes the peg slot while playing the game
	std::cout << "Enter a slot to place the peg into: ";
	// get a valid slot to place the peg into
	int temp = input_H_Included::getInteger();
	while (temp < 1 || temp > numberOfPegs) { // temp > numOfPegs
		std::cout << "You must enter a valid peg slot: ";
		temp = input_H_Included::getInteger();
	}
	pegSlot = temp - 1; // place the peg into that slot (-1 for the index value, not what the user sees)
}



void playTheGame(int winWidth, bool isCentered) { // from the main menu, executes the settings menu and eventually the game
	bool allowDupeColors, isPlaying = true; // allowDuplicateColor pegs in the code.  the user is playing the game
	int numOfTurns, numOfPegs, selectedPegColor = COLORS_PEGS::peg1, selectedPegSlot = 0, currTurn = 0, guessOption; // the number of turns, the number of pegs, the currently selected peg color and slot, the current turn, and the option that the user wants to execute
	settingsWindow(winWidth, isCentered, allowDupeColors, numOfTurns, numOfPegs); // open the settings window where the user can choose the settings for the game they are about to play

																				  // create a multidimensional array of pegs (represents the board)
	mastermind_peg_H_Included::Peg** pegs = new mastermind_peg_H_Included::Peg*[numOfTurns + 1]; // create a pointer of a pointer, number of turns + 1 rows for the secret code
	for (int i = 0; i < numOfTurns + 1; ++i) { // for each row
		pegs[i] = new mastermind_peg_H_Included::Peg[2 * numOfPegs]; // create the columns - number of pegs for the guesses, and then the same number of pegs for the informational pegs
	}
	populateBoard(pegs, numOfTurns, numOfPegs, allowDupeColors); // initialize the multidimensional array of pegs just declared

	while (isPlaying) { // while the user has not lost or won
		system("CLS"); // clear the screen
		mastermind_display_H_Included::play(winWidth, isCentered, pegs, numOfTurns, numOfPegs, false); // display the play menu
		displayAvailablePegs(); // display the pegs to choose from
		displayPegGuessOptions(selectedPegColor, selectedPegSlot); // display the options for the user to choose which to execute (changing peg color, slot, placing the peg, finishing the turn)
		setPegOptions(pegs, selectedPegColor, selectedPegSlot, numOfPegs, numOfTurns, currTurn, allowDupeColors, isPlaying, winWidth, isCentered); // set the option that the user chose to execute
	}

	std::cout << "\nContinuing to the main menu on keypress . . ." << std::endl;
	system("PAUSE>NUL");
}



void populateBoard(mastermind_peg_H_Included::Peg *pegArry[], int numberOfTurns, int numberOfPegs, bool allowDuplicateColors) { // populates the board of pegs, determined by how many turns and pegs the user chose
	for (int i = 0; i < numberOfTurns + 1; i++) { // for each turn (+1 for code)
		for (int j = 0; j < 2 * numberOfPegs; j++) { // for each guess peg and info peg
			pegArry[i][j].set(STATES_PEGS::inactive, COLORS_PEGS::pegInactive, numberOfTurns - i); // set the state to inactive, the color to inactive, and the current turn
			if (j >= numberOfPegs) { // if the peg is an info peg
				pegArry[i][j].setColor(COLORS_PEGS::pegInfoDefault); // set the color to the default info peg
			}
			if (i == 0) { // if the peg is on the first row (code row?)
				if (j < numberOfPegs) { // if it's not an info peg
					pegArry[i][j].set(STATES_PEGS::code, COLORS_PEGS::pegGuessDefault, numberOfTurns - i); // set the state to the code, set the color to a default guess, and the current turn
				}
				else { // if the peg is an info peg
					pegArry[i][j].setColor(COLORS::gray); // set the peg color to the background color of gray to make the peg not visible
				}
			}
			else if (i == numberOfTurns) { // if the row is the first guess
				if (j < numberOfPegs) { // if the peg isn't an info peg
					pegArry[i][j].setColor(COLORS_PEGS::pegGuessDefault); // set the color to the default peg guess
				}
			}
		}
	}
	createCode(pegArry, allowDuplicateColors, numberOfPegs); // create the code
}



void setInfoPegs(mastermind_peg_H_Included::Peg *pegArry[], int numberOfPegs, int numberOfTurns, int currentTurn) { // sets the info pegs (the pegs on the far right side of the board)
	/*	somewhat complicated following...

	this determines for each code peg, if there is one peg that matches that is the "best"

			ex: by best, if there are 5 blue pegs in the guess, and one blue peg in the code, it will NOT output 4 white info pegs and 1 red peg, but rather, only 1 red peg
				because that red info peg is of higher priority than a white info peg, we set it as the bestInfoType and the bestPegPosition

	for each code peg,
	look at each guess peg
		check if the color and position match with the code peg
			is the color and position the same as the code peg? then it should be a red peg for matching color and position, set the CURRENT peg to that info type
			is the color the same as the code peg?  then it should be a white peg for matching color ONLY, set the CURRENT peg to that info type
		after looking at the current guess peg, are these new values better than what was previously found from the other guess pegs?
			if so, make them the new best values (like searching for a maximum value algorithm but in terms of pegs)
	ONLY if a best position has been found (if there are ANY info pegs)
		then place that BEST peg onto the board
	move onto the next code peg and repeat!
*/
	int infoPegCount = 0;
	for (int i = 0; i < numberOfPegs; i++) { // for each guess peg
		int bestPegPosition = -1, currentInfoType = 0, bestInfoType = 0;
		for (int j = 0; j < numberOfPegs; j++) { // for each guess peg
			if (pegArry[0][i].getColor() == pegArry[numberOfTurns - currentTurn][j].getColor()) { // if the color is the same
				if (i == j) { // if the position is the same
					currentInfoType = 2; // it is matching color and position, set the currentInfoType to signify that.
				}
				else {
					currentInfoType = 1; // it is matching color ONLY, set the currentInfoType to signify that.
				}
				if (currentInfoType > bestInfoType) { // if the currentInfoType is better than what was previously found
					bestInfoType = currentInfoType; // set it to the new best
					bestPegPosition = j; // store the position of where this best peg was found
				}
			}
		}
		if (bestPegPosition > -1) { // if any info peg was found
									// place it, depending if it was...
			if (bestInfoType == 2) { // matching color and position...
				pegArry[numberOfTurns - currentTurn][numberOfPegs + infoPegCount].set(STATES_PEGS::info, COLORS_PEGS::pegInfoColorAndPositionMatch, currentTurn);
			}
			else { // or matching color only
				pegArry[numberOfTurns - currentTurn][numberOfPegs + infoPegCount].set(STATES_PEGS::info, COLORS_PEGS::pegInfoColorOnlyMatch, currentTurn);
			}
			infoPegCount++; // place the next info peg into the slot to the right
		}
	}
}



void setMenuOption(int &menuOption) { // sets an option from the main menu (1 instructions, 2 play, 3 scores, 4 quit)
	std::cout << "\n\nEnter an option: "; // ask for an option
	menuOption = input_H_Included::getInteger(); // get the option as an integer
	input_H_Included::checkInteger(menuOption, 1, 2, 3, 4); // check if the integer is an accepted option
}



void setPegOptions(mastermind_peg_H_Included::Peg *pegArry[], int &pegColor, int &pegSlot, int numberOfPegs, int numberOfTurns, int &currentTurn, bool allowDuplicateColors, bool &continueGame, int winWidth, bool isCentered) { // followup of displayPegGuessOptions.  executes the chosen option (changing peg color & slot, placing the peg, ending the turn)
	std::cout << "\nEnter an option: ";
	// get a valid peg option to execute
	int settingToChange = input_H_Included::getInteger();
	input_H_Included::checkInteger(settingToChange, 1, 2, 3, 4);

	switch (settingToChange) { // depending on the setting to change
	case 1: // change peg color
		playChangePegColor(pegColor);
		break;
	case 2: // change peg slot
		playChangePegSlot(pegSlot, numberOfPegs);
		break;
	case 3: // place peg
		pegArry[numberOfTurns - currentTurn][pegSlot].setState(STATES_PEGS::guess);
		pegArry[numberOfTurns - currentTurn][pegSlot].setColor(pegColor);
		break;
	case 4: // finish turn
		finishTurn(pegArry, numberOfPegs, numberOfTurns, currentTurn, allowDuplicateColors, continueGame, winWidth, isCentered);
		break;
	default:
		std::cout << "Unexpected case." << std::endl;
		break;
	}
}



void setSettingsOption(bool &changingSettings, bool &allowDuplicateColors, int &numberOfTurns, int &numberOfPegs) { // sets the settings for the game
	std::cout << "\nEnter an option: ";
	int settingToChange = input_H_Included::getInteger(); // get a valid integer for a setting to change
	input_H_Included::checkInteger(settingToChange, 1, 2, 3, 4); // check if that integer is one of the valid values

	int temp;
	switch (settingToChange) { // depending on the setting being changed
	case 1: // allow duplicate color pegs
		allowDuplicateColors = !allowDuplicateColors;
		break;
	case 2: // number of turns
		std::cout << "How many guesses would you like?: ";
		// get a valid value for the amount of guesses the user would like
		temp = input_H_Included::getInteger();
		while (temp < 1 || temp > 9) {
			std::cout << "You must enter a number between 1 and 9.  Try again: ";
			temp = input_H_Included::getInteger();
		}
		numberOfTurns = temp;
		break;
	case 3: // number of pegs
		std::cout << "How many pegs (per guess) would you like?: ";
		// get a valid value for the amount of pegs the user would like
		temp = input_H_Included::getInteger();
		while (temp < 1 || temp > 5) {
			std::cout << "You must enter a number between 1 and 5.  Try again: ";
			temp = input_H_Included::getInteger();
		}
		numberOfPegs = temp;
		break;
	case 4: // finish changing settings
		changingSettings = false; // the user is not changing settings anymore
		break;
	default:
		std::cout << "Unexpected case." << std::endl;
		break;
	}
}



void settingsWindow(int winWidth, bool isCentered, bool &allowDuplicateColors, int &numberOfTurns, int &numberOfPegs) { // holds all of the code for the settings window before starting a game
	bool isChangingSettings = true; // the user is changing settings

									// set default values of the settings able to be changed by the user
	allowDuplicateColors = true;
	numberOfTurns = 9;
	numberOfPegs = 5;

	do {
		system("CLS"); // clear the screen
		mastermind_display_H_Included::settings(winWidth, isCentered, allowDuplicateColors, numberOfTurns, numberOfPegs); // display the settings window
		setSettingsOption(isChangingSettings, allowDuplicateColors, numberOfTurns, numberOfPegs); // change a setting
	} while (isChangingSettings); // while the user is still changing settings
}



void sortScores(std::string scoresArry[], int scoresLength) { // sorts scores from best at the 0th index to worst at the scoresLength-1 index
	// modified bubble sort that is able to sort strings of scores with the expected format
	bool swapped = true;
	int j = 0;
	std::string temp;
	while (swapped) {
		swapped = false;
		j++;
		for (int i = 0; i < scoresLength - j; i++) {

			// find the exact score related to the score of format "[exactScore  AAA]    settings: no duplicates, x pegs, x turns
			int space1 = scoresArry[i].find_first_of(' '); // the index of the space of the ith string
			int space2 = scoresArry[i + 1].find_first_of(' '); // the index of the space of the ith + 1 string

			temp = "";
			std::string tempScore = scoresArry[i];
			for (int k = 1; k < space1; k++) {
				temp += tempScore[k];
			}
			int score1 = std::stoi(temp);

			temp = "";
			tempScore = scoresArry[i + 1];
			for (int k = 1; k < space2; k++) {
				temp += tempScore[k];
			}
			int score2 = std::stoi(temp);



			if (scoresArry[i] > scoresArry[i + 1]) { // if the score is bigger than the next score, swap the two
				temp = scoresArry[i];
				scoresArry[i] = scoresArry[i + 1];
				scoresArry[i + 1] = temp;
				swapped = true;
			}
		}
	}
}
