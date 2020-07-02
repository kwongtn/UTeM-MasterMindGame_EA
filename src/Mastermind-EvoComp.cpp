// Mastermind-EvoComp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "params.h"
#include "utils.h"
#include "chromosome.h"

array<int, GENE_SIZE> userSelection;
unsigned short int generationCount = 0;
double maxFitnessHist = numeric_limits<double>::min();

json stats = {};

// Function to calculate and return max fitness in the chromosomes
double maxFitness(vector<Chromosome> chrs) {
	double maxVal = numeric_limits<double>::min();

	for (Chromosome chr : chrs) {
		if (chr.getFitness() > maxVal) {
			maxVal = chr.getFitness();
		}
	}

	// To look into historical data too
	maxVal > maxFitnessHist ? maxFitnessHist = maxVal : 0;

	return maxVal;
}

// Function to calculate and return index of the best chromosome
int bestFitnessIndex(vector<Chromosome> chrs) {
	double bestFitness = numeric_limits<double>::min();
	int bestFitnessIndex = -1;

	for (int i = 0; i < chrs.size(); i++) {
		if (chrs[i].getFitness() > bestFitness) {
			bestFitness = chrs[i].getFitness();
			bestFitnessIndex = i;
		}
	}

	return bestFitnessIndex;
}

// Function to calculate and return index of the worst chromosome
int worstFitnessIndex(vector<Chromosome> chrs) {
	double worstFitness = numeric_limits<double>::max();
	int worstFitnessIndex = -1;

	for (int i = 0; i < chrs.size(); i++) {
		if (chrs[i].getFitness() < worstFitness) {
			worstFitness = chrs[i].getFitness();
			worstFitnessIndex = i;
		}
	}

	return worstFitnessIndex;
}

// Function to calculate and return min fitness in the chromsomes
double minFitness(vector<Chromosome> chrs) {
	double minVal = numeric_limits<double>::max();

	for (Chromosome chr : chrs) {
		if (chr.getFitness() < minVal) {
			minVal = chr.getFitness();
		}
	}

	return minVal;
}

// Function to calculate and return average fitness in the chromosomes
double avgFitness(vector<Chromosome> chrs) {
	double totalFitness = 0;

	for (Chromosome chr : chrs) {
		totalFitness += chr.getFitness();
	}

	return totalFitness / POP_SIZE;
}


int main()
{

	srand((unsigned int)time(NULL));
	// Open output file
	ofstream outputCSV, outputJSON;
	string fileName = "../results/" + returnDatetimeString();
	outputCSV.open(fileName + ".csv");
	outputJSON.open(fileName + ".json");
	if (outputCSV.is_open()) {
		cout << "CSV File Save Path : " << fileName << ".csv" << endl;
	}
	else {
		cout << "CSV File Error." << endl;
		pause();
	}
	if (outputJSON.is_open()) {
		cout << "JSON File Save Path: " << fileName << ".json" << endl;
		outputJSON.close();
	}
	else {
		cout << "JSON File Error." << endl;
		pause();
	}

	cout << endl;

	std::chrono::steady_clock::time_point begin;

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
		begin = std::chrono::steady_clock::now();
	}
	else {
		// Randomly initialize values
		for (int i = 0; i < GENE_SIZE; i++) {
			userSelection[i] = timeRand() % GENE_SIZE;
		}
	}

	begin = std::chrono::steady_clock::now();
	// Initialize chromosomes with random values
	vector<Chromosome> chromosomes;
	for (int i = 0; i < POP_SIZE; i++) {
		chromosomes.push_back(userSelection);
	}

	// Output inputted values
	clearScreen();
	cout << "Target values: " << endl;
	for (int i = 0; i < GENE_SIZE; i++) {
		cout << setw(10) << left << userSelection[i];
	}
	cout << endl;
	for (int i = 0; i < GENE_SIZE; i++) {
		cout << setw(10) << left << colourNames[userSelection[i]];
	}

	cout << endl;
	printLine(30);

	if (OUTPUT) {
		// Output stats
		cout << endl << "Statistics:" << endl << endl;
		cout << setw(15) << left << "Generation"
			<< setw(25) << left << "Min Fitness"
			<< setw(25) << left << "Max Fitness"
			<< setw(25) << left << "Avg Fitness"
			<< setw(25) << left << "Best Chromosome"
			<< endl;

		printLine(15 + (25 * 4));

	}
	else {
		cout << "Program running, " << endl;
	}

	while (true) {
		// Generate chromosome list and write into json
		json chrList = {};
		for (int i = 0; i < POP_SIZE; i++) {
			chromosomes[i].getGenesAsString();
			chrList.push_back({
				{"chrString", chromosomes[i].getGenesAsString()},
				{"fitness", chromosomes[i].getFitness()}
				});
		}


		// Write stats to variable
		stats.push_back({
			{"gen", generationCount},
			{"avgFitness", avgFitness(chromosomes)},
			{"minFitness", minFitness(chromosomes)},
			{"maxFitness", maxFitness(chromosomes)},
			{"bestChr", chromosomes[bestFitnessIndex(chromosomes)].getGenesAsString()},
			{"worstChr", chromosomes[worstFitnessIndex(chromosomes)].getGenesAsString()},
			{"chrs", chrList}
			});

		if (OUTPUT) {
			cout << setw(15) << right << stats[generationCount]["gen"]
				<< setw(25) << right << stod(to_string(stats[generationCount]["minFitness"]))
				<< setw(25) << right << stod(to_string(stats[generationCount]["maxFitness"]))
				<< setw(25) << right << stod(to_string(stats[generationCount]["avgFitness"]))
				<< "              "
				<< setw(25) << left << returnString(stats[generationCount]["bestChr"])
				<< endl;

		}
		else {
			cout << "\rGeneration " << generationCount << ".";
		}

		// Write stats and related values into csv file 
		if (generationCount == 0) {
			outputCSV << "Generation, MinFitness, MaxFitness, HistoricalMaxFitness, AvgFitness, Best Chromosome" << endl;
		}
		outputCSV << generationCount << ", "
			<< stats[generationCount]["minFitness"] << ", "
			<< stats[generationCount]["maxFitness"] << ", "
			<< maxFitnessHist << " , "
			<< stats[generationCount]["avgFitness"] << ", "
			<< returnString(stats[generationCount]["bestChr"])
			<< endl;

		// Check for termination criteria
		if (stats[generationCount]["maxFitness"] >= 0.9999999999999999) {
			cout << "\n\nTermination criteria: Achieved Target Sequence at generation "
				<< generationCount << ". " << endl;
			break;
		}
		else if (generationCount == MAX_CYCLES) {
			cout << "\n\nTermination criteria: Achieved maximum cycles of " << MAX_CYCLES << ". " << endl;
			break;
		}

		// Parent selection
		array<int, 2> parentIndex;
		for (int i = 0; i < 2; i++) {
			int tournament[2];
			tournament[0] = rand() % POP_SIZE;
			while (true) {
				tournament[1] = rand() % POP_SIZE;
				if (tournament[0] != tournament[1]) {
					break;
				}
			}

			if (chromosomes[tournament[0]].getFitness() > chromosomes[tournament[1]].getFitness()) {
				parentIndex[i] = tournament[0];
			}
			else {
				parentIndex[i] = tournament[1];

			}


		}

		array<array<int, GENE_SIZE>, 2> childrenGenes;
		childrenGenes[0] = chromosomes[parentIndex[0]].getGenes();
		childrenGenes[1] = chromosomes[parentIndex[1]].getGenes();

		// Crossover
		if (((rand() % 100) / 100) < CRSVR_RATE) {
			stats[generationCount]["crossover"] = true;
			int crossoverPoint = rand() % GENE_SIZE;
			for (int i = crossoverPoint; i < GENE_SIZE; i++) {
				int temp = childrenGenes[0][i];
				childrenGenes[0][i] = childrenGenes[1][i];
				childrenGenes[1][i] = temp;
			}

		}
		else {
			stats[generationCount]["crossover"] = false;
		}

		// Mutation
		for (int i = 0; i < childrenGenes.size(); i++) {
			if (((rand() % 100) / 100) < MUTATION_RATE) {
				string mutationString = "mutation" + i;
				stats[generationCount][mutationString] = true;
				childrenGenes[i][rand() % GENE_SIZE] = colors[rand() % SEL_SIZE];

			}
			else {
				string mutationString = "mutation" + i;
				stats[generationCount][mutationString] = false;

			}

		}

		// Select and forfeit chromosomes, replace with children. The worst and one other random chromosome will be replaced.
		chromosomes[worstFitnessIndex(chromosomes)] = Chromosome(userSelection, childrenGenes[0]);
		while (true) {
			int index = rand() % POP_SIZE;
			if (index != worstFitnessIndex(chromosomes)) {
				chromosomes[index] = Chromosome(userSelection, childrenGenes[1]);
				break;
			}
		}

		// Loop
		generationCount++;
	}

	string temp = "";
	cout << endl;
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	// Write stats into JSON File
	cout << "Writing into JSON File.";
	outputJSON.open(fileName + ".json");
	outputJSON << stats.dump(2);
	outputJSON.close();
	cout << "\rRuntime: " << (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) / 1000000.0 << " seconds. " << endl << endl;

	cout << "Program end. Please type \"e\" to really exit the program: ";
	getline(cin, temp, 'e');
	pause();

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
