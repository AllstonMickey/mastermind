// Allston Mickey - 06/03/16
#ifndef display_H_Included
#define display_H_Included

#include <iostream>
#include <string>
#include <Windows.h>
#include <stdio.h>

void resizeWindow(int widthRes[], int heightRes[]); // resizes a window based on columns and lines from console
void resizeWindow_WIN10(int widthRes[], int heightRes[], int selectedRes); // resizes the window, supplied the array of resolutions and which resolution to resize to, only works on Windows 10
void populateResolutionsArray(int widthRes[], int heightRes[]); // takes in two arrays, width and height of a resolution, and then populates them
std::string centerStringToWindow(int winWidth, int lengthOfString); // returns a string of spaces that centers a string of some length in a window of some width
void centerStringToWindow(int winWidth, std::string &s); // adds spaces to the beginning of string s to center that string in a window of some width
void setConsoleColor(int foregroundColorNumber); // sets the console text/foreground color to the foregroundColorNumber and the background color to default black
void setConsoleColor(int foregroundColorNumber, int backgroundColorNumber); // sets the console text to the foregroundColorNumber and the background color to backgroundColorNumber



void resizeWindow(int widthRes[], int heightRes[]) { // resizes the console window based on the numbers of columns and lines
	widthRes[0] = 800; // sets the default resolution width
	heightRes[0] = 600; // sets the default resolution height
	system("MODE CON COLS=95 LINES=35"); // size is approximately: COLS = res / 8.4, LINES =  res / 17.1
}



void resizeWindow_WIN10(int widthRes[], int heightRes[], int selectedRes) { // resizes the window, supplied the array of resolutions and which resolution to resize to, only works on Windows 10
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions
	MoveWindow(console, r.left, r.top, widthRes[selectedRes], heightRes[selectedRes], TRUE); // moves the window to the coordinates of a rectangle and sets the resolution
}



void populateResolutionsArray(int widthRes[], int heightRes[]) { // takes in two arrays, width and height of a resolution, and then populates them
	widthRes[0] = 800; heightRes[0] = 600; // small 4:3 resolution
	widthRes[1] = 1024; heightRes[1] = 768; // med 4:3 resolution
	widthRes[2] = 1280; heightRes[2] = 960; // large 4:3 resolution
}



std::string centerStringToWindow(int winWidth, int lengthOfString) { // returns a string of spaces that centers a string of some length in a window of some width
	std::string centerAlignment = ""; // holds the spaces required to center a string of some length
	int numOfSpacesToCenter = (int)(((winWidth / 8.5) - lengthOfString) / 2); // number of spaces required to add to the beginning of a string to make it centered in respect to the current window size and the string length
	for (int i = 0; i < numOfSpacesToCenter; i++) { // for each space required to center,
		centerAlignment += " "; // add that space to the "centering" string
	}

	return centerAlignment; // return the "centering" string
}



void centerStringToWindow(int winWidth, std::string &s) { // adds spaces to the beginning of string s to center that string in a window of some width
	std::string centerAlignment = ""; // holds the spaces required to center a string of some length
	int numOfSpacesToCenter = (int)(((winWidth / 8.5) - s.length()) / 2); // number of spaces required to add to the beginning of a string to make it centered in respect to the current window size and the string length
	for (int i = 0; i < numOfSpacesToCenter; i++) { // for each space required to center
		centerAlignment += " "; // add that space to the "centering" string
	}

	s.insert(0, centerAlignment); // insert the "centering" string at the very beginning of the string to shift the string to the center
}



void setConsoleColor(int foregroundColorNumber) { // sets the console text/foreground color to the foregroundColorNumber and the background color to default black
	HANDLE handleColor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handleColor, foregroundColorNumber);
}



void setConsoleColor(int foregroundColorNumber, int backgroundColorNumber) { // sets the console text to the foregroundColorNumber and the background color to backgroundColorNumber
	HANDLE handleColor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handleColor, (backgroundColorNumber * 16) + foregroundColorNumber);
}



#endif
