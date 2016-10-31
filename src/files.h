// Allston Mickey - 06/03/16
#ifndef files_H_Included
#define files_H_Included

#include <fstream>
#include <iostream>

int countWords(std::ifstream &fileToParse, char delimiter); // counts the number of words
void parseWords(std::ifstream &fileToParse, std::string words[], char delimiter); // parses words from a file and adds them to an array of strings
void readFile(std::ifstream &fileToRead, std::string path); // reopens a file with some path



// each word MUST END with a delimiter!
int countWords(std::ifstream &fileToParse, char delimiter) { // count the number of words in a file
	char charScan; // variable of char to check for characters in the file being parsed
	int wordCount = 0; // number of words
	while (!fileToParse.eof()) { // while not at the end of file
		fileToParse >> std::noskipws >> charScan; // read the next character (including whitespaces: noskipws)
		if (charScan == delimiter) { // if a delimiter is scanned
			wordCount++; // increment the number of words
		}
	}

	return wordCount - 1; // return the wordCount
	/* RETURNS -1 IF NO WORDS ARE FOUND */
}



// each word MUST END with a delimiter!
void parseWords(std::ifstream &fileToParse, std::string words[], char delimiter) { // parses words from a file and adds them to an array of strings
	char charScan; // variable of char to check for characters in the file being parsed
	int wordCount = 0; // number of words
	std::string tempWord = ""; // holds the temporary word until a delimiter is found
	while (!fileToParse.eof()) { // while not at the end of file
		fileToParse >> std::noskipws >> charScan; // read the next character (including whitespaces: noskipws)
		if (charScan != delimiter) { // if a delimiter is not scanned
			tempWord += charScan; // add the character to the total word
		}
		else if (charScan == delimiter) { // if a delimiter is scanned
			if (!fileToParse.eof()) { // if you're not at the end of the file (prevents crashing when a delimiter is at the end of file)
				words[wordCount] = tempWord; // the word of the count index is the total word before the delimiter
				tempWord = ""; // reset the temp/total word
				wordCount++; // increment the word count
			}
		}
	}
}

void readFile(std::ifstream &fileToRead, std::string path) { // reopens a file from some path
	fileToRead.close(); // close the file
	fileToRead.open(path); // reopen the file from its path
}
#endif
