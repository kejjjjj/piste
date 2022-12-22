#include "piste.h"

void Cell::AddVelocity(const ImVec2& amount)
{
	vel.x += amount.x;
	vel.y += amount.y;
}
void Cell::LimitVelocity(const float limit)
{

	if (vel.x > limit)
		vel.x = limit;
	else if (vel.x < -limit)
		vel.x = -limit;
	

	if (vel.y > limit)
		vel.y = limit;
	else if (vel.y < -limit)
		vel.y = -limit;
}
void Cell::OnDeath()
{
	ImVec2 subtracted = ImVec2(this->pos.x - gen::goal.x, this->pos.y - gen::goal.y);
	this->distance_to_goal = sqrt(subtracted.x * subtracted.x + subtracted.y * subtracted.y) / 4;
	this->alive = false;
	return SetFitness();
}
void Cell::SetFitness()
{
	if (finished) {
		fitness = 1.0 / 16.0 + 10000.0 / ((float)(brain.steps_taken * brain.steps_taken) / 2);

		return;
	}
	fitness = 1.0 / (float)(distance_to_goal * distance_to_goal);
}
void Cell::Move()
{
	if (!this->alive)
		return;

	if (brain.steps_taken > brain.GetInstructionCount() || this->brain.steps_taken > gen::min_step) {
		return OnDeath();
	}
	
	acc = brain.directions[brain.steps_taken];
	brain.steps_taken++;

	AddVelocity(acc);
	LimitVelocity(5);
	
	pos.x += vel.x;
	pos.y += vel.y;

	//pos = ImClamp(pos, ImVec2(0, 0), ImVec2(ui.iPixelsPerAxis.x, ui.iPixelsPerAxis.y));


}
void Cell::Update()
{
	if (!alive)
		return;

	Move();

	if (pos.x < 1 || pos.x > ui.iPixelsPerAxis.x || pos.y < 1 || pos.y > ui.iPixelsPerAxis.y) {
		return OnDeath();
	}

	//	ui.DrawRect(ImVec2(0, 100), 200, 2, COL::BLACK);
	//	ui.DrawRect(ImVec2(ui.iPixelsPerAxis.x - 100, 150), 100, 2, COL::BLACK);
	//	ui.DrawRect(ImVec2(0, 200), 200, 2, COL::BLACK);

	if (pos.y < 105 && pos.y > 100 && pos.x > 0 && pos.x < 200) {
		return OnDeath();
	}
	if (pos.y < 205 && pos.y > 200 && pos.x > 0 && pos.x < 200) {
		return OnDeath();
	}
	if (pos.y < 155 && pos.y > 150 && pos.x > (ui.iPixelsPerAxis.x - 100)) {
		return OnDeath();
	}



	ImVec2 subtracted = ImVec2(gen::goal.x - this->pos.x, gen::goal.y - this->pos.y);
	this->distance_to_goal = sqrt(subtracted.x * subtracted.x + subtracted.y * subtracted.y);

	if (distance_to_goal < 2) {
		alive = false;
		finished = true;
		SetFitness();
	}

}