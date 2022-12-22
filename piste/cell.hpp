#pragma once

#ifndef _cell
#define _cell

#include "piste.h"

class Cell
{
public:

	Cell(const int instructions)  : brain(instructions) {};


	void Update();
	void Move();
	void OnDeath();
	void SetFitness();
	void AddVelocity(const ImVec2& amount);
	void LimitVelocity(const float limit);
	Cell Clone() { return *this; }

	ImVec2 pos = ImVec2(ui.iPixelsPerAxis.x / 2, ui.iPixelsPerAxis.y / 2), acc, vel;
	bool alive = true;
	bool finished = false;
	float distance_to_goal = 0.f;
	double fitness = 0.;
	Brain brain;
private:
};

#endif