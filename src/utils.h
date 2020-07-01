#pragma once

#include <iostream>
#include <iomanip>
#include <time.h>
#include <sstream>
#include <chrono>

using namespace std;

// Utility file for commonly used functions

inline void printLine(int length = 30, char character = '=') {
	for (int i = 0; i < length; i++) {
		cout << character;
	}

	cout << "\n";
}

// Prompts the user to input anything to continue
inline void pause() {
	cout << endl;
	system("pause");
}

// Clears the screen
inline void clearScreen() {
	system("cls");
}

inline int timeRand() {
	return rand();
}

// Validates the user input and returns an integer if an integer is input
inline int inputInt(bool prompter = true, bool forceInput = true) {
	std::string myString = "";
	int i;
	while (true) {
		cin.clear();
		if (prompter) {
			cout << "\n> ";
		}
		getline(cin, myString);

		if (myString == "" && !forceInput) {
			return -1000;
		}

		try
		{
			i = stoi(myString);
			break;
		}
		catch (std::invalid_argument const& e)
		{
			cout << "Bad input: std::invalid_argument thrown. Please re-input." << '\n';
			!prompter ? prompter = !prompter : prompter;
			continue;
		}
		catch (std::out_of_range const& e)
		{
			cout << "Integer overflow: std::out_of_range thrown. Please re-input." << '\n';
			!prompter ? prompter = !prompter : prompter;
			continue;
		}

	}

	return i;

}

inline bool decider(std::string custString = "Your selection (y / n): ") {
	bool x = true;
	std::string selection;
	while (true) {
		cout << custString;
		try {
			getline(cin, selection);
			if (selection == "y" || selection == "Y") {
				x = true;
				break;
			}
			else if (selection == "n" || selection == "N") {
				x = false;
				break;
			}
			else {
				throw "Error";
			}
			if (cin.fail() || selection != "y" || selection != "Y" || selection != "n" || selection != "N") {
				throw "Error";
			}
		}
		catch (...) {
			cout << "Please enter a valid character." << endl;
			pause();
		}
	}
	return x;

}

template <typename T>
inline bool checkExistInArray(array<T, SEL_SIZE> myArray, T check) {
	for (int i = 0; i < myArray.size(); i++) {
		if (myArray[i] == check) {
			return true;
		}
	}
	return false;
}

inline std::string returnDatetimeString(bool includeDashes = false)
{
	time_t t = time(nullptr);
	struct tm nowTime;
	localtime_s(&nowTime, &t);

	std::stringstream ss;
	ss << nowTime.tm_year + 1900;
	if (includeDashes) { ss << "-"; }
	ss << nowTime.tm_mon;
	if (includeDashes) { ss << "-"; }
	ss << nowTime.tm_mday;
	if (includeDashes) { ss << "-"; }
	ss << nowTime.tm_hour;
	if (includeDashes) { ss << ":"; }
	ss << nowTime.tm_min;
	if (includeDashes) { ss << ":"; }
	ss << nowTime.tm_sec;

	return ss.str();
}


string returnString(json myString) {
	return myString;
}