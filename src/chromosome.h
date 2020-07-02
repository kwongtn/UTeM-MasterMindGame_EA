#pragma once

#include "params.h"
#include "utils.h"

// Declare chromosome object and other required data
class Chromosome {
private:
	//declare an integer array with length GENE_SIZE
	array<int, GENE_SIZE> genes;
	array<int, SEL_SIZE> selectionCounts = { 0 };
	double fitness = 0.00;

public:
	void calcFitness(array<int, GENE_SIZE>);
	double getFitness();
	array<int, GENE_SIZE> getGenes();
	int getGene(int);
	string getGenesAsString();

	~Chromosome();
	Chromosome();
	Chromosome(array<int, GENE_SIZE>);
};

// Destructor
Chromosome::~Chromosome() {}

// Constructor, will initialize with random values
Chromosome::Chromosome() {
	for (int i = 0; i < GENE_SIZE; i++) {
		genes[i] = rand() % SEL_SIZE;
	}

	// Calculate the number of occurences of each color
	for (int i = 0; i < genes.size(); i++) {
		selectionCounts[genes[i]]++;
	}

}

// Constructor, will take the values and place into the genes variable within this object
Chromosome::Chromosome(array<int, GENE_SIZE> arr) {
	for (int i = 0; i < GENE_SIZE; i++) {
		genes[i] = arr[i];
	}

	// Calculate the number of occurences of each color
	for (int i = 0; i < arr.size(); i++) {
		selectionCounts[arr[i]]++;
	}

}

// Count and set fitness function, with resect to the input array
void Chromosome::calcFitness(array<int, GENE_SIZE> arr) {
	// Places the count of each possible selection into the array
	array<int, SEL_SIZE> counts = { 0 };
	for (int i = 0; i < arr.size(); i++) {
		counts[arr[i]]++;
	}

	/*
		 Calculates and count the values with the correct color in correct position.
		 If a target is hit the fitness value is added, counts are decreased.
	*/
	for (int i = 0; i < arr.size(); i++) {
		if (arr[i] == genes[i]) {
			fitness += (double)1 / GENE_SIZE;
			counts[arr[i]]--;
		}
	}

	/*
		 Calculates the values with the correct colour in the wrong position.
		 Consider the following table, given means the generated values, want means the true values, multiplier is the number to be multiplied towards the fitness fraction:
		 ===============================
		 Given       | 3 | 5 | 5
		 Want        | 2 | 1 | 7
		 ------------|-------------
		 Multiplier  | 2 | 1 | 5
		 ===============================
		 Therefore, we can conclude that the multiplier the the minimum of these 2 values.
	*/
	for (int i = 0; i < counts.size(); i++) {
		fitness += (double)min(counts[i], selectionCounts[i]) / ((double)2 * GENE_SIZE);
	}

}

// Get whole gene as array
array<int, GENE_SIZE> Chromosome::getGenes() {
	return genes;
}

// Get specific gene index
int Chromosome::getGene(int i){
	return genes[i];
}

// Get fitness
double Chromosome::getFitness() {
	return fitness;
}

// Get genes as String
string Chromosome::getGenesAsString() {
	string myString = "";
	for (int i = 0; i < genes.size(); i++) {
		myString += to_string(genes[i]) + " ";
	}
	myString.pop_back();
	return myString;
}