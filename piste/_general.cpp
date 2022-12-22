#include "piste.h"


void gen::main()
{
	static Population population(1000);


	if (GetAsyncKeyState(VK_NUMPAD0) & 1) {
		ImVec2 pos = fromAngleToVec2(0.01f);
		std::cout << "angle 0.01 -> (" << pos.x << ", " << pos.y << ")\n";
		std::cout << "random(1): " << random(2.0 * PI) << '\n';
		population.active = true;
		gen::goal = ImVec2(ui.iPixelsPerAxis.x / 2, 10);
		population.Reset();
	}

	ui.Clear(COL::WHITE);
	if (population.active) {


		population.Update();

		population.active = population.GenerationActive();

		std::for_each(population.population.begin(), population.population.end(), [](Cell* cell)
			{
				ui.Draw(cell->pos, COL::BLACK);
			});


		if (!population.active) {
			population.NewGeneration();
			population.active = true;
			population.Reset();
			Sleep(500);
		}

	}
	ui.DrawRect(ImVec2(0, 100), 200, 2, COL::BLACK);
	ui.DrawRect(ImVec2(0, 200), 200, 2, COL::BLACK);

	ui.DrawRect(ImVec2(ui.iPixelsPerAxis.x - 100, 150), 100, 2, COL::BLACK);

	ui.Draw(gen::goal, COL::RED);
}