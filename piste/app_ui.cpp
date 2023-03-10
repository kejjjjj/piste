#include "piste.h"

bool AppUI::Construct(const ImVec2& a_mins, const ImVec2& a_maxs, const float& gridSize,  const bool& border, const ImVec4& bg_col, const ImVec4& tile_col, const ImVec4 _borderCol) {

	//if (bIsConstructed)
	//	return true;

	if (!ImGui::GetCurrentContext()) {
		FatalError("AppUI::Construct failed with: ImGui::GetCurrentContext() == 0");
		return false;
	}

	//if (ImGui::GetCurrentContext()->CurrentWindow) {
	//	const ImVec2 wnd_pos = ImGui::GetWindowPos();
	//	const ImVec2 wnd_size = ImGui::GetWindowSize();

	//	if (a_mins.x < wnd_pos.x || a_mins.y < wnd_pos.y || (wnd_pos.x + wnd_size.x) < a_maxs.x || (wnd_pos.y + wnd_size.y) < a_maxs.y) {

	//		//FatalError("AppUI::Construct failed with: Set bounds are not within the window bounds");

	//		return false;
	//	}
	//}

	dwTimeCreated = Sys_MilliSeconds();
	fGridSize = gridSize < 1 ? 8 : gridSize;
	bgCol = bg_col;
	tileCol = tile_col;
	borderCol = _borderCol;

	mins = a_mins;
	maxs = a_maxs;
	bIsConstructed = true;

	fWidth = maxs.x - mins.x;
	fHeight = maxs.y - mins.y;

	real_mins = ImVec2(mins.x, mins.y);
	real_maxs = ImVec2(maxs.x - 16, maxs.y - 36);

	bBorder = border;

	int x_pixel_count = real_maxs.x - real_mins.x;
	int y_pixel_count = real_maxs.y - real_mins.y;

	x_pixel_count /= fGridSize;
	y_pixel_count /= fGridSize;

	fAspectRatio = float(x_pixel_count) / float(y_pixel_count);


	uPixels = (int)(x_pixel_count + y_pixel_count) / (fGridSize);

	if (uPixels <= 0)		uPixels = 1;
	if (x_pixel_count <= 0)	x_pixel_count = 1;
	if (y_pixel_count <= 0)	y_pixel_count = 1;

	vPixelSize = ImVec2((x_pixel_count + y_pixel_count) / x_pixel_count * (fGridSize / 2), 
						(x_pixel_count + y_pixel_count) / y_pixel_count * (fGridSize / 2));

	vPixelSize.x = (int)vPixelSize.x;
	vPixelSize.y = (int)vPixelSize.y;

	if (vPixelSize.x > vPixelSize.y)
		vPixelSize.y = vPixelSize.x;
	else
		vPixelSize.x = vPixelSize.y;

	
	iPixelsPerAxis.x = x_pixel_count;
	iPixelsPerAxis.y = y_pixel_count;

	real_maxs.x = real_mins.x + ((iPixelsPerAxis.x) * vPixelSize.x);
	real_maxs.y = real_mins.y + ((iPixelsPerAxis.y) * vPixelSize.y);

	uPixels *= uPixels;

	return true;
}
void AppUI::Render()
{

	if (!bIsConstructed)
		return;

	//for (int y = 0; y < iPixelsPerAxis.y; y++) {

	//	for (int x = 0; x < iPixelsPerAxis.x; x++) {

	//		Draw(ImVec2(x, y), ImVec4(rand() % 255, rand() % 255, rand() % 255, 255));

	//	}

	//}
	gen::main();

	if (bBorder) {

		//all the 1 means gridSize


		//left
		gui::DrawRectangleFilled(ImVec2(mins.x, mins.y), ImVec2(mins.x + 1, real_maxs.y), borderCol);


		//top
		gui::DrawRectangleFilled(ImVec2(mins.x, mins.y), ImVec2(real_maxs.x, mins.y + 1), borderCol);

		//right
		gui::DrawRectangleFilled(ImVec2(real_maxs.x - 1, mins.y),	real_maxs, borderCol);

		//bottom
		gui::DrawRectangleFilled(ImVec2(mins.x, real_maxs.y - 1),	real_maxs, borderCol);
	}

	ImGui::Dummy(ImVec2(real_maxs.x - real_mins.x, real_maxs.y - real_mins.y + 10));

}