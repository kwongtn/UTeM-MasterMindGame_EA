#pragma once

#include "params.h"

// TODO: Declare chromosome object and other required data
class Chromosome {
private:
	//declare an integer array with length GENE_SIZE
	array<int,GENE_SIZE> genes;
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
	int randNum;
	srand(time(NULL));

	//since this current template array is 1 dimensional?
	for (int i = 0; i < GENE_SIZE; i++)
		{
			randNum = rand() % 8 ;
			genes[i] = randNum;
		}
		
}

// TODO: Constructor, will take the values and place into the genes variable within this object
Chromosome::Chromosome(array<int, GENE_SIZE> arr) {
	
	
	for (int i = 0; i < GENE_SIZE; i++)
		{
			genes[i] = arr[i];
		}
}

// TODO: Count and set fitness function, with resect to the input array
void Chromosome::countFitness(array<int, GENE_SIZE> arr) {
	int totalresult = 0;
		for (int i = 0; i < GENE_SIZE; i++)
		{
			if (arr[i] == genes[i])
			{
				totalresult = totalresult + 0.25;
			}
			//Not sure how to check for correct colour in wrong position
		}
		fitness = totalresult;
}

// TODO: Get whole gene as array
array<int, GENE_SIZE> Chromosome::getGenes() {

	// Return array
	return genes;
}

// TODO: Get specific gene index
int Chromosome::getGene(int i)
{

	// Return the gene at that position
	return 0;
}

// TODO: Get fitness
double Chromosome::getFitness() {

	// Return fitness
	return 0.01;
}

// Get genes as String
string Chromosome::getGenesAsString() {
	string myString = "";
	for (int i = 0; i < genes.size(); i++) {
		myString += genes[i] + " ";
	}
	myString.pop_back();

	return myString;
}