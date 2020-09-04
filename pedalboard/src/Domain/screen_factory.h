#pragma once
#include "screen.h"

class ScreenFactory {
public:
	virtual Screen* CreateScreen(int screenNumber);
};