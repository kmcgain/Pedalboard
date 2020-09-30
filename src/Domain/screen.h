#pragma once

#include "function/function.h"
#include "preset.h"

class Screen {
public:
	virtual void DisplayFunction(FunctionState* functionState, Preset* currentPreset) = 0;
};