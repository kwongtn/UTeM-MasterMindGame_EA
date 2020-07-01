#pragma once

#include "params.h"

// TODO: Declare chromosome object and other required data
class Chromosome {
private:
	array<int, GENE_SIZE> genes;
	double fitness;


public:
	void countFitness(array<int, GENE_SIZE>);
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

// TODO: Constructor, will initialize with random values
Chromosome::Chromosome() {

}

// TODO: Constructor, will take the values and place into the genes variable within this object
Chromosome::Chromosome(array<int, GENE_SIZE> arr) {

}

// TODO: Count and set fitness function, with resect to the input array
void Chromosome::countFitness(array<int, GENE_SIZE> arr) {

}

// TODO: Get whole gene as array
array<int, GENE_SIZE> Chromosome::getGenes() {

	// Return array
}

// TODO: Get specific gene index
int Chromosome::getGene(int i)
{

	// Return the gene at that position
}

// TODO: Get fitness
double Chromosome::getFitness() {

	// Return fitness
// Get genes as String
string Chromosome::getGenesAsString() {
	string myString = "";
	for (int i = 0; i < genes.size(); i++) {
		myString += genes[i] + " ";
	}
	myString.pop_back();

	return myString;
}