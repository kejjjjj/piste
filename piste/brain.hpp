#pragma once

#ifndef _brain
#define _brain

#include <ranges>

#include "piste.h"
class Brain
{
public:
	Brain(const int32_t steps);
	~Brain();

	void Create(const int32_t steps) {
		std::mt19937 mt;
		for (auto i : std::views::iota(0, steps)) {
			
			directions.push_back(fromAngleToVec2(random(2.f * PI)));
		}
		
	}
	void Mutate()
	{
		float rate = 0.05f;
		std::for_each(directions.begin(), directions.end(), [&rate](ImVec2& dir) 
			{
				if (random(1.f) < rate) {
					dir = fromAngleToVec2(random(2.f * PI));
				}
			});
	}
	Brain Copy() { return *this; }

	int32_t steps_taken = 0;
	int32_t GetInstructionCount() { return directions.size() - 1; }

	std::vector<ImVec2> directions; //used for acceleration
};

#endif