#pragma once
#ifndef appwin
#define appwin
#include "piste.h"


class AppWindow
{
public:

	AppWindow() : Size(), Pos(), open(true), active() {}
	//void CornerActionButtons();

	ImVec2 Size;
	ImVec2 Pos;
	bool active;
	bool open;

private:
};

#endif