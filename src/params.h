#pragma once

#include <iostream>
#include <vector>
#include <cstring>
#include <array>
#include <fstream>
#include <limits>
#include <vector>
#include "libs/json.hpp"

using namespace std;
using json = nlohmann::json;

// Gene size
const int GENE_SIZE = 4;

// Selection size
const int SEL_SIZE = 8;

// Population size
const int POP_SIZE = 10;

/*
  Terminate when reached this number of cycles.
*/
const int MAX_CYCLES = 100;

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

const array<int, SEL_SIZE> colors = {
	0, 1, 2, 3, 4, 5, 6, 7
};

const array<string, SEL_SIZE> colourNames = {
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
const bool DUP_GENE = true;

/*
	Rates of each function occurence used in this program.
	MUT_RATE -> Mutation Rate
	CRSVR_RATE -> Crossover Rate
*/
const double MUTATION_RATE = 0.5;
const double CRSVR_RATE = 0.5;

// The number of crossover points in a single chromosome
const int CRSVR_COUNT = 1;

// Whether to output intermediatery messages
const bool OUTPUT = true;