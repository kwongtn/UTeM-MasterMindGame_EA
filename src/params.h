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
	 POP_SIZE    -> Population size, how many chromosomes per generation.
	 CRSVR_COUNT ->The number of crossover points in a single chromosome, no use for now
	 TOURNAMENT_SIZE  -> The number or values to take for tournament during parent selection via tournament.
	 EXPER_COUNT -> Number of experiments to run
*/
const int 
	GENE_SIZE = 4,
	SEL_SIZE = 8,
	POP_SIZE = 10,
	CRSVR_COUNT = 1,
	TOURNAMENT_SIZE = 2
	EXPER_COUNT = 1000
;

/*
	 DUP_GENE    -> If duplicates are accepted. If accepted, a chromosome can have more than one of the same gene. No use for now.
	 OUTPUT      -> Whether to output stats of each generation.
	 AUTO_LOOP   -> Whether to loop multiple experiments as fast as possible.
	 FILE_OUTPUT -> Whether to output files. Recommended for this to be disable when AUTO_LOOP is true.
	 MAX_CYCLES  Terminate when reached this number of cycles.
*/
const bool 
	DUP_GENE = true,
	OUTPUT = true,
	AUTO_LOOP = true,
	FILE_OUTPUT = true
;


/*
	Rates of each function occurence used in this program.
	MUT_RATE -> Mutation Rate
	CRSVR_RATE -> Crossover Rate
*/
const double 
  MUTATION_RATE = 0.5,
	CRSVR_RATE = 0.5
;

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