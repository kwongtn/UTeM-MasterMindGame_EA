// Mastermind-EvoComp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "params.h"
#include "utils.h"
#include "chromosome.h"

array<int, GENE_SIZE> userSelection;

int main()
{
	// TODO: Open output file


	// Request user input, error catch on each attempt
	cout << "Do you want to input selection? If no, a random sequence will be selected." << endl;
	if (decider()) {
		// Generate menu and user inputs, showing current selected ones.
		for (int i = 0; i < GENE_SIZE; i++) {
			while (true) {
				clearScreen();
				cout << "Current Available Selections:" << endl;
				for (int j = 0; j < colors.size(); j++) {
					cout << setw(5) << left << colors[j] << setw(20) << left << colourNames[j] << endl;
				}

				cout << endl;

				cout << "Current selection : ";
				for (int k = 0; k < i; k++) {
					cout << colors[userSelection[k]] << "(" << colourNames[userSelection[k]] << "), ";
				}

				cout << endl << endl;

				// Get user inputs
				cout << "Please input " << GENE_SIZE << " colours for your selection. ";
				cout << "For gene " << i + 1 << ": ";
				int tempInt = inputInt();
				if (!checkExistInArray(colors, tempInt)) {
					cout << "Invalid value, please re-input." << endl;
					pause();
				}
				else {
					userSelection[i] = tempInt;
					break;
				}

			}
		}
	}
	else {
		// Randomly initialize values
		for (int i = 0; i < GENE_SIZE; i++) {
			userSelection[i] = timeRand() % GENE_SIZE;
		}
	}

	// TODO: Initialize chromosomes

				cout << endl << endl;

				// Get user inputs
				cout << "Please input " << GENE_SIZE << " colours for your selection. ";
				cout << "For gene " << i + 1 << ": ";
				int tempInt = inputInt();
				if (!checkExistInArray(colors, tempInt)) {
					cout << "Invalid value, please re-input." << endl;
					pause();
				}
				else {
					userSelection[i] = tempInt;
					break;
				}

			}
		}
	}
	else {
		// Randomly initialize values
		for (int i = 0; i < GENE_SIZE; i++) {
			userSelection[i] = timeRand() % GENE_SIZE;
		}
	}

	// Output inputted values
	clearScreen();
	cout << "The current inputs are: " << endl;
	for (int i = 0; i < GENE_SIZE; i++) {
		cout << setw(10) << left << userSelection[i];
	}
	cout << endl;
	for (int i = 0; i < GENE_SIZE; i++) {
		cout << setw(10) << left << colourNames[userSelection[i]];
	}
	cout << endl;

	// Initialize chromosomes with random values
	array<Chromosome, POP_SIZE> chromosomes;

	// Trigger to calculate fitness function
	for (int i = 0; i < POP_SIZE; i++) {
		chromosomes[i].countFitness(userSelection);
	}

	// TODO: Output stats


	// TODO: Write stats and related values into file 


	// TODO: Check for termination criteria


	// TODO: Parent selection


	// TODO: Crossover


	// TODO: Mutation


	// TODO: Select and forfeit chromosomes, replace with children


	// TODO: Loop


	// TODO: Show this if program terminates


}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
