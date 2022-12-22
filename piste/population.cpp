#include "piste.h"

void Population::Update()
{
	std::for_each(population.begin(), population.end(), [](Cell* cell) 
		{ 
			cell->Update(); 
		});

}
void Population::Reset()
{
	std::for_each(population.begin(), population.end(), [](Cell* cell) 
		{
			cell->pos = ImVec2(ui.iPixelsPerAxis.x / 2, ui.iPixelsPerAxis.y - 1); 
			cell->acc = ImVec2(0,0);
			cell->vel = ImVec2(0,0);
			cell->alive = true;
			cell->finished = false;
			cell->distance_to_goal = 1000;
			cell->brain.steps_taken = 0;
			cell->fitness = 0;
		});
}
bool Population::GenerationActive()
{
	bool all_are_dead = true;

	std::for_each(population.begin(), population.end(), [&all_are_dead](const Cell* cell)
		{
			if (cell->alive) {
				all_are_dead = false;

			}
		});

	return !all_are_dead;
}
float Population::FitnessSum()
{
	float sum = 0;
	std::for_each(population.begin(), population.end(), [&sum](const Cell* cell) {sum += cell->fitness; });

	return sum;
}
void Population::NewGeneration()
{
	static std::vector<Cell> newCells;
	if (newCells.empty()) {
		for (auto i : population)
			newCells.push_back(*i);
	}

	const auto GetRandomParent = [this]() -> Cell* {

		float rand = random(FitnessSum());
		float runningSum = 0;

		for (auto i : population) {
			runningSum += i->fitness;

			if (runningSum > rand)
				return i;
		}

		return nullptr;
	};

	Cell best = SetBestCell();

	newCells[0] = best;

	for (int i = 1; i < population.size(); i++) {

		Cell* parent = GetRandomParent();

		newCells[i] = *parent;

	}

	int j = 0;
	for (auto& i : population) {
		i = &newCells[j];
		j++;

		i->brain.Mutate();
	}
	gen::gen++;
}
Cell Population::SetBestCell()
{
	//const Cell* best = *std::max_element(population.cbegin(), population.cend(), [](const Cell* i, const Cell* j) { return i->fitness <= j->fitness; });

	Cell* best = 0;
	float highest_fitness = 0;

	for (auto i : population) {

		if (i->fitness >= highest_fitness) {
			highest_fitness = i->fitness;
			best = i;
		}

	}

	if (!best) {
		FatalError("*std::max_element(population.cbegin(), population.cend(), [](const Cell* i, const Cell* j) { return i->fitness < j->fitness; });");
		
	}

	if (best->finished && best->brain.steps_taken < gen::min_step) {
		gen::min_step = best->brain.steps_taken;
		std::cout << "step: " << gen::min_step << '\n';
	}

	return *best;
}