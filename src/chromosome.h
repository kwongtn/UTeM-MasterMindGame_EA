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
	cout << "Initialized " << endl;
}

// TODO: Constructor, will take the values and place into the genes variable within this object
Chromosome::Chromosome(array<int, GENE_SIZE> arr) {

}

// TODO: Count and set fitness function, with resect to the input array
void Chromosome::countFitness(array<int, GENE_SIZE> arr) {

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