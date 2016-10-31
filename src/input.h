// Allston Mickey - 06/03/16
#ifndef input_H_Included
#define input_H_Included

#include <iostream>
#include <string>
#include <sstream>

bool isAbleToStoi(std::string input); // checks if a string is able to be converted to an integer without crashing the program (true if it will not crash)
bool isIntegerGood(int input, int acceptedInput1, int acceptedInput2, int acceptedInput3); // returns true if the input is one of the four accepted values, false if not
bool isIntegerGood(int input, int acceptedInput1, int acceptedInput2, int acceptedInput3, int acceptedInput4); // returns true if the input is one of the four accepted values, false if not
bool isLetters(std::string input); // checks if an input is all letters
int getInteger(); // gets an integer as input
std::string intToStr(int number); // converts an integer to a string
void checkInteger(int &input, int acceptedInput1, int acceptedInput2, int acceptedInput3); // checks if an integer is one of the four accepted inputs using isIntegerGood as the check
void checkInteger(int &input, int acceptedInput1, int acceptedInput2, int acceptedInput3, int acceptedInput4); // checks if an integer is one of the four accepted inputs using isIntegerGood as the check
void strToUpper(std::string &phraseToUpper); // converts a string to uppercase



bool isAbleToStoi(std::string input) { // checks if a string is able to be converted to an integer without crashing the program (true if it will not crash)
	for (int i = 0; i < input.length(); i++) { // for each character
		int ascii = (int)input[i]; // the ascii number is the character of the entry converted to an integer
		if ((ascii < 48 || ascii > 57) && ascii != 45) { // if the character entered is not a number or a hyphen
			return false; // then the input string is not able to be converted to an integer without crashing the program
		}
	}
	// if the whole input has been scanned without any characters that will cause a crash when converting, then
	return true; // return the input string is able to be converted to a string
}



bool isIntegerGood(int input, int acceptedInput1, int acceptedInput2, int acceptedInput3) { // returns true if the input is one of the three accepted values, false if not
	return ((input == acceptedInput1) || (input == acceptedInput2) || (input == acceptedInput3)); // returns if the input is one of the accepted
}



bool isIntegerGood(int input, int acceptedInput1, int acceptedInput2, int acceptedInput3, int acceptedInput4) { // returns true if the input is one of the four accepted values, false if not
	return ((input == acceptedInput1) || (input == acceptedInput2) || (input == acceptedInput3) || (input == acceptedInput4)); // returns if the input is one of the accepted
}



bool isLetters(std::string input) { // checks if an input is all letters
	strToUpper(input); // convert the input to uppercase to ignore cases
	for (int i = 0; i < input.length(); i++) { // for each character
		if ((int)input[i] < 65 || (int)input[i] > 90) { // if it's not a letter
			return false; // return that it's not a letter
		}
	}
	return true; // if each character in the input is a letter, return that it's a letter
}



int getInteger() { // gets an integer as input
	std::string input; // string to hold the user's input
	std::cin >> input; // get the user's input
	while (!isAbleToStoi(input)) { // while the user does not enter a valid integer as their input
		std::cout << "An integer must be input!  Try again: "; // ask them again for an integer
		std::cin >> input; // get the user's input
	}
	return std::stoi(input); // return the user's valid input, converted to an integer
}



std::string intToStr(int number) { // converts an integer to a string
	std::stringstream ss; // create a string stream
	ss << number; // send the int to the stream
	return ss.str(); // return the string of the int number
}



void checkInteger(int &input, int acceptedInput1, int acceptedInput2, int acceptedInput3) {
	while (!isIntegerGood(input, acceptedInput1, acceptedInput2, acceptedInput3)) { // while the integer is not one of the accepted inputs
		std::cerr << "Invalid.  Enter '" << acceptedInput1 << "', '" << acceptedInput2 << "', or '" << acceptedInput3 << "': "; // display the possible valid inputs
		input = getInteger(); // get another integer
	}
}



void checkInteger(int &input, int acceptedInput1, int acceptedInput2, int acceptedInput3, int acceptedInput4) { // checks if an integer is one of the four accepted inputs using isIntegerGood as the check
	while (!isIntegerGood(input, acceptedInput1, acceptedInput2, acceptedInput3, acceptedInput4)) { // while the integer is not one of the accepted inputs
		std::cerr << "Invalid.  Enter '" << acceptedInput1 << "', '" << acceptedInput2 << "', '" << acceptedInput3 << "', or '" << acceptedInput4 << "': "; // display the possible valid inputs
		input = getInteger(); // get another integer
	}
}



void strToUpper(std::string &phraseToUpper) { // converts a string to uppercase
	int length = phraseToUpper.length(); // get the length of the phrase
	for (int i = 0; i < length; i++) { // for each character in the string
		phraseToUpper[i] = toupper(phraseToUpper[i]); // make it uppercase
	}
}
#endif
