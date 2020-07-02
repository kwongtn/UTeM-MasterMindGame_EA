// Mastermind-EvoComp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "params.h"
#include "utils.h"
#include "chromosome.h"

unsigned short int experimentCount = 1;
int totalGenerations = 0;
int lowestGen = numeric_limits<int>::max();
int lowestGenExperiment = 0;
int maxGen = numeric_limits<int>::min();
int maxGenExperiment = 0;
double maxFitnessHist = numeric_limits<double>::min();

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

string fileNameGen() {
	string myString = "../results/" + returnDatetimeString() + "-";
	if (experimentCount < 100) {
		myString += "0";
	}
	if (experimentCount < 10) {
		myString += "0";
	}
	myString += to_string(experimentCount);
	return myString;
}

int main()
{


	unsigned short int generationCount = 0;
	while (true) {
		clearScreen();
		//srand((unsigned int)time(NULL));

		array<int, GENE_SIZE> userSelection;

		json stats = {};

		// Open output file
		ofstream outputCSV, outputJSON;
		string fileName = fileNameGen();
		if (FILE_OUTPUT) {

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

		}
		else {
			cout << "File output disabled." << endl;
		}

		cout << endl;

		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

		// Randomly initialize values
		for (int i = 0; i < GENE_SIZE; i++) {
			userSelection[i] = timeRand() % SEL_SIZE;
		}


		// Initialize chromosomes with random values
		vector<Chromosome> chromosomes;
		for (int i = 0; i < POP_SIZE; i++) {
			chromosomes.push_back(userSelection);
		}

		cout << "\nExperiment #" << experimentCount << endl;
		if (generationCount > 0) {
			cout << "Average generations per experiment: " << totalGenerations / (experimentCount - 1) << endl;

		}
		cout << "Lowest generation count: " << lowestGen << " @ " << lowestGenExperiment << endl;
		cout << "Max generation count: " << maxGen << " @ " << maxGenExperiment << endl;
		cout << endl;

		// Output inputted values
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
				if (!AUTO_LOOP) {
					cout << "\rGeneration " << generationCount << ".";

				}
			}

			if (FILE_OUTPUT) {
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

			}

			// Check for termination criteria
			if (stats[generationCount]["maxFitness"] == 1) {
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
			totalGenerations++;
		}

		string temp = "";
		cout << endl;
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		if (FILE_OUTPUT) {
			// Write stats into JSON File
			cout << "Writing into JSON File.";
			outputJSON.open(fileName + ".json");
			outputJSON << stats.dump(2);
			outputJSON.close();

		}
		cout << "\rRuntime: " << (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) / 1000000.0 << " seconds. " << endl << endl;

		outputCSV.close();

		cout << "Average generations per experiment: " << totalGenerations / experimentCount << endl;

		cout << "\nExperiment #" << experimentCount++ << " end. ";
		if (!AUTO_LOOP) {
			cout << "Do you want to continue next experiment ? \n";
			if (!decider()) {
				break;
			}

		}
		maxFitnessHist = numeric_limits<double>::min();
		if (generationCount > maxGen) {
			maxGen = generationCount;
			maxGenExperiment = experimentCount;
		}
		if (generationCount < lowestGen) {
			lowestGen = generationCount;
			lowestGenExperiment = experimentCount;
		}
		generationCount = 0;
	}
	cout << "Program end.";
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
