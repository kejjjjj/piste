#include "piste.h"


DWORD Sys_MilliSeconds()
{
	return timeGetTime() - sys_baseTime;
}