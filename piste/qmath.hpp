#pragma once

#ifndef qmath
#define qmath

#include "piste.h"

ImVec2 fromAngleToVec2(const float angle);
float random(const float range); //0 -> HI
float random(const float min, const float range); //LO -> HI

#endif