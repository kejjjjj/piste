#include "piste.h"

Brain::Brain(const int32_t direction)
{
	srand(time(NULL));
	for (auto i : std::views::iota(0, direction)) { 
		directions.push_back(fromAngleToVec2(random(2.f * PI)));
	}
}
Brain::~Brain() {
	directions.clear();
	directions.resize(0);
}