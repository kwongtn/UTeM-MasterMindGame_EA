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

/*
   GENE_SIZE   -> How many selections. For example, " 0 3 2 2 " means 4 selections.
	 SEL_SIZE    -> The space size for selection to occur. Refer to colours & colourNames variable below. 
	                Number here should not be more than the number of elements in the variables.
	 POP_SIZE    -> Population size, how many chromosomes per generation. Recommended 30 for small genes.
	 CRSVR_COUNT ->The number of crossover points in a single chromosome.
	 TOURNAMENT_SIZE  -> The number or values to take for tournament during parent selection via tournament.
	 EXPER_COUNT -> Number of experiments to run
	 REPLACEMENT_COUNT  -> How many chromosomes to be replaced by children, must be a multiplier of 2
*/
const int 
	GENE_SIZE = 15,
	SEL_SIZE = 10,
	POP_SIZE = 30,
	CRSVR_COUNT = 3,
	TOURNAMENT_SIZE = 6,
	MAX_CYCLES = 100000,
	EXPER_COUNT = 100,
	REPLACEMENT_COUNT = 16
;

static_assert(REPLACEMENT_COUNT % 2 == 0, "REPLACEMENT_COUNT must be a multiplier of 2.");
static_assert(REPLACEMENT_COUNT < POP_SIZE, "REPLACEMENT_COUNT must not be larger than POP_SIZE.");

/*
	 DUP_GENE    -> If duplicates are accepted. If accepted, a chromosome can have more than one of the same gene. No use for now.
	 OUTPUT      -> Whether to output stats of each generation.
	 AUTO_LOOP   -> Whether to loop multiple experiments as fast as possible.
	 FILE_OUTPUT -> Whether to output files. Recommended for this to be disable when AUTO_LOOP is true.
	 MAX_CYCLES  Terminate when reached this number of cycles.
*/
const bool 
	DUP_GENE = true,
	OUTPUT = false,
	AUTO_LOOP = true,
	FILE_OUTPUT = true,
	JSON_OUTPUT = false,
	EXPRESS_MODE = true
;


/*
	Rates of each function occurence used in this program.
	MUT_RATE -> Mutation Rate
	CRSVR_RATE -> Crossover Rate
*/
const double 
  MUTATION_RATE = 0.1,
	CRSVR_RATE = 0.9
;
static_assert(MUTATION_RATE < 1, "MUTATION_RATE must not be larger than 1.");
static_assert(CRSVR_RATE < 1, "CRSVR_RATE must not be larger than 1.");

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
 - 9  : Turquoise
 - 10 : Maroon
*/

const vector<int> colors = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9
};

const vector<string> colourNames = {
	"Red",
	"Green",
	"Blue",
	"Yellow",
	"Brown",
	"Orange",
	"Black",
	"White",
	"Turquoise",
	"Maroon"
};
