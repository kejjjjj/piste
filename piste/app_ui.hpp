#pragma once

#ifndef appui
#define appui

#include "piste.h"

class AppUI
{
public:
	bool Construct(const ImVec2& a_mins, const float& w, const float& h, const float& gridSize = -1, const bool& border = true, const ImVec4& bg_col = COL::WHITE, const ImVec4& tile_col = COL::BLACK, const ImVec4 _borderCol = COL::WHITE) {
		return Construct(a_mins, ImVec2(a_mins.x + w, a_mins.y + h), gridSize, border, bg_col, tile_col, _borderCol);
	}


	bool Construct(const ImVec2& a_mins, const ImVec2& a_maxs, const float& gridSize = -1, const bool& border = true, const ImVec4& bg_col = COL::WHITE, const ImVec4& tile_col = COL::BLACK, const ImVec4 _borderCol = COL::WHITE);

	bool IsConstructed() { return bIsConstructed; }
	void Kill() { bIsConstructed = false; }

	void Render();


	void Draw(const ImVec2& Pixel, const ImVec4& col) {
		return gui::DrawRectangleFilled(

			ImVec2(real_mins.x + (Pixel.x * vPixelSize.x),					real_mins.y + Pixel.y * vPixelSize.y), //mins
			ImVec2(real_mins.x + (Pixel.x * vPixelSize.x) + vPixelSize.x,	real_mins.y + (Pixel.y * vPixelSize.y) + vPixelSize.y), col); //maxs
	}
	void DrawRect(const ImVec2& Pixel, const int w, const int h, const ImVec4& col) {
		return gui::DrawRectangleFilled(

			ImVec2(real_mins.x + (Pixel.x * vPixelSize.x), real_mins.y + Pixel.y * vPixelSize.y), //mins
			ImVec2(real_mins.x + ((Pixel.x + w) * vPixelSize.x) + vPixelSize.x, real_mins.y + ((Pixel.y + h) * vPixelSize.y) + vPixelSize.y), col); //maxs
	}
	void Clear(const ImVec4& col) { gui::DrawRectangleFilled(real_mins, real_maxs, col); };


	ImVec2 GetWindowPos() const noexcept { return real_mins; }
	ImVec2 GetWindowSize() const noexcept { return ImVec2(real_maxs.x - real_mins.x, real_maxs.y - real_mins.y); }
	int32_t GetHorzCenter() const noexcept { return real_maxs.x - (real_maxs.x - real_mins.x) / 2; }
	
	ImVec2 GetContentRegionAvail() const { 
		const ImGuiWindow* wnd = ImGui::GetCurrentWindow(); 
	
		return ImVec2(real_maxs.x - wnd->DC.CursorPos.x, real_maxs.y - wnd->DC.CursorPos.y);
	}
	bool ButtonCentered(const char* label, float alignment = 0.5f, ImVec2 _size = ImVec2(0,0))
	{
		ImGuiStyle& style = ImGui::GetStyle();

		float size = ImGui::CalcTextSize(label).x * 1.5f + style.FramePadding.x * 2.0f;
		float avail = GetContentRegionAvail().x;

		float off = (avail - size) * alignment;
		if (off > 0.0f)
			ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);

		return ImGui::Button(label, _size);
	}


	bool bIsConstructed = 0;

	int32_t uPixels = 0;
	ImVec2i iPixelsPerAxis;
	float fAspectRatio = 0;
	
private:

	ImVec2 mins, maxs;
	ImVec2 real_mins, real_maxs;
	float fWidth = 0, fHeight = 0;
	float fGridSize = -1.f;
	float fTimeElapsed = 0.f; 
	//float fPadding = 0.f;
	bool bBorder = true;
	ImVec4 bgCol;
	ImVec4 tileCol;
	ImVec4 borderCol;
	DWORD dwTimeCreated = 0;
	ImVec2 vPixelSize;

};

inline AppUI ui;

#endif