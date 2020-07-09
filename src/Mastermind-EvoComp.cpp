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
vector<int> histGenCount(EXPER_COUNT);

long double totalTime = 0;
vector<long double> histTimeUse(EXPER_COUNT);

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

string counterString() {
	string myString = "";
	if (experimentCount < 100) {
		myString += "0";
	}
	if (experimentCount < 10) {
		myString += "0";
	}
	myString += to_string(experimentCount);
	return myString;
}

inline string fileNameGen() {
	string myString = "../results/" + returnDatetimeString() + "-";
	return myString;
}


int main()
{

	unsigned short int generationCount = 0;
	string
		globalFilename = "../results/globalResults.csv",
		localFileName = fileNameGen() + "summary.csv",
		trackerFileName = "../results/tracker.txt";

	// Open tracker
	ifstream trackerIn;
	ofstream trackerOut;
	bool trackerExists = false;
	trackerIn.open(trackerFileName);
	if (!trackerIn.is_open()) {
		cout << "Tracker file does not exist, creating..." << endl;
		trackerOut.open(trackerFileName);
		trackerOut << "Do not remove this file, else the globalResults will be overwritten on next run." << endl;
		trackerOut.close();
	}
	else {
		trackerExists = true;
	}

	trackerIn.close();

	// Open global file
	ofstream outputCSV_global,
		outputCSV_summary;
	if (trackerExists) {
		outputCSV_global.open(globalFilename, ofstream::app);

	}
	else {
		outputCSV_global.open(globalFilename);
		outputCSV_global << "timestamp, populationSize, maxGen, minGen, sdGen, avgGen, maxTime, minTime, sdTime, avgTime, mutationRate, crossoverRate, experimentCount, replacementRate, replacementCount" << endl;
	}

	outputCSV_summary.open(localFileName);
	outputCSV_summary << "timestamp, popSize, gen, time, mutationRate, crossoverRate, experimentCount, replacementRate, replacementCount" << endl;

	srand((unsigned int)time(NULL));
	cout << "GENE_SIZE = " << GENE_SIZE << endl;
	cout << "SEL_SIZE = " << SEL_SIZE << endl;
	cout << "POP_SIZE = " << POP_SIZE << endl;
	cout << "CRSVR_RATE = " << CRSVR_RATE << endl;
	cout << "MUTATION_RATE = " << MUTATION_RATE << endl;
	cout << "TOURNAMENT_SIZE = " << TOURNAMENT_SIZE << endl;
	cout << "REPLACEMENT_RATE = " << (double)REPLACEMENT_COUNT / POP_SIZE << endl;
	cout << "REPLACEMENT_COUNT = " << REPLACEMENT_COUNT << endl;
	cout << "Possible Combinations = " << pow(SEL_SIZE, GENE_SIZE) << endl << endl;
	pause();

	while (true) {
		clearScreen();

		array<int, GENE_SIZE> userSelection;

		json stats = {};

		// Open output file
		ofstream
			outputCSV_detailed,
			outputJSON
			;
		string fileName = fileNameGen() + counterString();
		if (FILE_OUTPUT) {
			outputCSV_detailed.open(fileName + ".csv");
			if (outputCSV_detailed.is_open()) {
				cout << "CSV File Save Path : " << fileName << ".csv" << endl;
			}
			else {
				cout << "CSV File Error." << endl;
				pause();
			}

			// Check for JSON Output toggle
			if (JSON_OUTPUT) {
				outputJSON.open(fileName + ".json");
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
				cout << "JSON File Output disabled." << endl;
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
		if (experimentCount > 1) {
			int avgGen = ceil(totalGenerations / (experimentCount - 1));
			cout << "Average generations per experiment: " << avgGen << endl;
			cout << "Experiments having the average generations: ";

			for (int i = 0; i < histGenCount.size(); i++) {
				if (histGenCount[i] == avgGen) {
					cout << i << ", ";
				}
			}

			cout << endl;

		}
		cout << "Lowest generation count: " << lowestGen << " @ " << lowestGenExperiment << endl;
		cout << "Max generation count: " << maxGen << " @ " << maxGenExperiment << endl;
		cout << "Generation standard deviation: " << standardDeviation(histGenCount) << endl;
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
					<< setw(25) << right << stod(to_string(round(stats[generationCount]["avgFitness"] * 1000) / 1000))
					<< "              "
					<< setw(25) << left << returnString(stats[generationCount]["bestChr"])
					<< endl;

			}
			else {
				if (!(generationCount % 10)) {
					cout << "\rGeneration " << generationCount << ".";

				}

			}

			if (FILE_OUTPUT) {
				// Write stats and related values into csv file 
				if (generationCount == 0) {
					outputCSV_detailed << "Generation, MinFitness, MaxFitness, HistoricalMaxFitness, AvgFitness, Best Chromosome" << endl;
				}
				outputCSV_detailed << generationCount << ", "
					<< stats[generationCount]["minFitness"] << ", "
					<< stats[generationCount]["maxFitness"] << ", "
					<< maxFitnessHist << " , "
					<< round(stats[generationCount]["avgFitness"] * 100000) / 100000 << ", "
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

			// Getting offspring with respect to REPLACEMENT_COUNT
			vector<Chromosome> offspring;
			for (int offspringCounter = 0; offspringCounter < REPLACEMENT_COUNT; offspringCounter++) {
				// Parent selection
				array<int, 2> parentIndex;
				for (int i = 0; i < 2; i++) {
					vector<int> tournaments;
					tournaments.push_back(rand() % POP_SIZE);
					for (int j = 0; j < TOURNAMENT_SIZE; j++) {
						while (true) {
							int tournament = rand() % POP_SIZE;
							if (!checkExistInArray(tournaments, tournament)) {
								tournaments.push_back(tournament);
								break;
							}
						}
					}

					double bestFitInd = numeric_limits<double>::min();
					for (int j : tournaments) {
						if (chromosomes[j].getFitness() > chromosomes[bestFitInd].getFitness()) {
							bestFitInd = j;
						}
					}

					parentIndex[i] = bestFitInd;


				}

				array<array<int, GENE_SIZE>, 2> childrenGenes;
				childrenGenes[0] = chromosomes[parentIndex[0]].getGenes();
				childrenGenes[1] = chromosomes[parentIndex[1]].getGenes();

				// Crossover
				if (rand() % 100 < CRSVR_RATE * 100) {
					stats[generationCount]["crossover"] = true;
					int crsvrs = rand() % CRSVR_COUNT + 1;

					// Determining crossover points
					vector<int> crsvrPoints;
					for (int i = 0; i < crsvrs; i++) {
						int temp = rand() % GENE_SIZE;
						if (i != 0) {
							while (checkExistInArray(crsvrPoints, temp)) {
								temp = rand() % GENE_SIZE;
							}
						}

						crsvrPoints.push_back(temp);

					}

					for (int i = 0; i < crsvrs; i++) {
						for (int crsvrCount = crsvrPoints[i]; crsvrCount < GENE_SIZE; crsvrCount++) {
							swap(childrenGenes[0][crsvrCount], childrenGenes[1][crsvrCount]);
						}

					}

				}
				else {
					stats[generationCount]["crossover"] = false;

				}

				// Mutation
				for (int i = 0; i < childrenGenes.size(); i++) {
					if (rand() % 100 < MUTATION_RATE * 100) {
						string mutationString = "mutation" + i;
						stats[generationCount][mutationString] = true;
						childrenGenes[i][rand() % GENE_SIZE] = colors[rand() % SEL_SIZE];

					}
					else {
						string mutationString = "mutation" + i;
						stats[generationCount][mutationString] = false;

					}

				}

				offspring.push_back(Chromosome(userSelection, childrenGenes[0]));
				offspring.push_back(Chromosome(userSelection, childrenGenes[1]));

			}

			// Sort Chromosomes
			chromosomes = sortChromosome(chromosomes);

			// Set chromosomes to replace
			vector<int> replacement;
			replacement.push_back(0); // To replace the worst chromosome
			replacement.push_back(1); // To replace the 2nd worst chromosome

			// Set to replace remaining chromosomes randomly
			for (int i = 2; i < REPLACEMENT_COUNT; i++) {
				int temp = rand() % POP_SIZE;
				while (checkExistInArray(replacement, temp)) {
					temp = rand() % POP_SIZE;
				}
				replacement.push_back(temp);
			}

			// Replacing
			for (int i = 0; i < REPLACEMENT_COUNT; i++) {
				chromosomes[replacement[i]] = offspring[i];
			}

			// Loop
			generationCount++;
			totalGenerations++;
		}

		string temp = "";
		cout << endl;
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		if (JSON_OUTPUT) {
			// Write stats into JSON File
			cout << "Writing into JSON File.";
			outputJSON.open(fileName + ".json");
			outputJSON << stats.dump(2);
			outputJSON.close();

		}

		long double runtime = (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) / 1000000.0;
		cout << "\rRuntime: " << runtime << " seconds. " << endl << endl;

		outputCSV_detailed.close();

		cout << "Average generations per experiment: " << totalGenerations / experimentCount << endl;

		// Write into localfile summary
		outputCSV_summary
			<< returnDatetimeString(true) << ", "
			<< POP_SIZE << ", "
			<< generationCount << ", "
			<< runtime << ", "
			<< MUTATION_RATE << ", "
			<< CRSVR_RATE << ", "
			<< experimentCount << ", "
			<< (double)REPLACEMENT_COUNT / POP_SIZE << ", "
			<< REPLACEMENT_COUNT
			<< endl
			;

		cout << "\nExperiment #" << experimentCount << " end. ";
		if (!AUTO_LOOP) {
			cout << "Do you want to continue next experiment ? \n";
			if (!decider()) {
				break;
			}

		}

		if (EXPER_COUNT == experimentCount) {
			cout << "Reached present experiment count of " << EXPER_COUNT << ". ";
			break;
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

		totalTime += runtime;
		histTimeUse[experimentCount - 1] = runtime;
		histGenCount[experimentCount - 1] = generationCount;
		experimentCount++;
		generationCount = 0;
	}
	outputCSV_summary.close();


	// Write into global results
	outputCSV_global
		<< returnDatetimeString(true) << ", "
		<< POP_SIZE << ", "
		<< maxGen << ", "
		<< lowestGen << ", "
		<< standardDeviation(histGenCount) << ", "
		<< totalGenerations / EXPER_COUNT << ", "
		<< getMax(histTimeUse) << ", "
		<< getMin(histTimeUse) << ", "
		<< standardDeviation(histTimeUse) << ", "
		<< totalTime / EXPER_COUNT << ", "
		<< MUTATION_RATE << ", "
		<< CRSVR_RATE << ", "
		<< EXPER_COUNT << ", "
		<< (double)REPLACEMENT_COUNT / POP_SIZE << ", "
		<< REPLACEMENT_COUNT
		<< endl
		;
	outputCSV_global.close();

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
