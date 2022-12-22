#pragma once

#ifndef mndwnd
#define mndwnd
#include "piste.h"

inline bool UPDATE_VIEWPORT = false;
inline float VIEWPORT_GRID = 3;
inline ImVec2 VIEWPORT_SIZE(800, 800);

namespace MW
{

	void RenderTabBar();
	void TabBarAction(const char* text, std::function<void()> a);
	void ButtonAction(const char* text, std::function<void()> a);
	void ToggleAction(const char* text, bool& var, std::function<void()> a);

}
#endif