#include "IDSheet.h"

using namespace std;

string ScancodeToString(SDL_Scancode scancode)
{
	string s;
	if (scancode >= SDL_SCANCODE_A && scancode <= SDL_SCANCODE_Z)
	{
		s.push_back((int)scancode + 61);
		return s;
	}
	else if (scancode >= SDL_SCANCODE_1 && scancode <= SDL_SCANCODE_9)
	{
		s.push_back((int)scancode + 19);
		return s;
	}

	switch (scancode)
	{
	case SDL_SCANCODE_0:
		s = "0";
		break;
	}
	return s;
}

int ExpSheet(int level)
{
	switch (level)
	{
	case 1:			return 100;
	case 2:			return 120;
	case 3:			return 140;
	case 4:			return 160;
	case 5:			return 180;
	case 6:			return 220;
	case 7:			return 280;
	case 8:			return 360;
	case 9:			return 500;
	case 10:		return 200;
	case 11:		return 200;
	case 12:		return 200;
	case 13:		return 200;
	case 14:		return 200;
	case 15:		return 200;
	}
    return NULL;
}
