#pragma once

#ifndef _population
#define _population

#include "piste.h"

class Population
{
public:
	Population(const int32_t cells){
		std::cout << "Population(constructor): allocating " << cells * sizeof(Cell) << " bytes of memory\n";

		for (auto i : std::views::iota(0, cells)) {
			Cell* cell = new Cell(1000); // a new brain with 1000 instructions
			cell->alive = true;
			population.push_back(cell);
		}
	}
	~Population() {
		std::cout << "clear memory\n";
		for (auto i : population) {
			delete i;
		}
		population.clear();
		population.resize(0);
	}

	void Update();
	void Reset();
	bool GenerationActive();
	float FitnessSum();
	void NewGeneration();
	Cell SetBestCell();

	std::vector<Cell*> population;
	bool active = false;


};

#endif