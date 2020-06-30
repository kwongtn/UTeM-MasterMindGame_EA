#pragma once

#include <iostream>
#include <vector>
#include <cstring>
#include <array>
#include <fstream>

using namespace std;

/*
 Define available characters, with the following conversion convention:
 - 1	: Red
 - 2	: Green
 - 3	: Blue
 - 4	: Yellow
 - 5	: Brown
 - 6	: Orange
 - 7	: Black
 - 8	: White
*/

const array<int, GENE_SIZE> colors = {
	1, 2, 3, 4, 5, 6, 7, 8
};

const array<string, GENE_SIZE> colourNames = {
	"Red",
	"Green",
	"Blue",
	"Yellow",
	"Brown",
	"Orange",
	"Black",
	"White"
};

/* 
   If duplicates are accepted. 
   if accepted, a chromosome can have more than one of the same gene.
*/
const bool DUP_GENE = false;

/*
  Rates of each function occurence used in this program.
	MUT_RATE -> Mutation Rate
	CRSVR_RATE -> Crossover Rate
*/
const double MUTATION_RATE = 0.5;
const double CRSVR_RATE = 0.5;

const int GENE_SIZE = 8;
