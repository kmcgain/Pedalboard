#pragma once

#include "function/function.h"
#include "preset.h"
#include "tuner.h"

class Screen {
public:
	virtual void DisplayFunction(FunctionState* functionState, Preset* currentPreset, TunerData& tuner) = 0;
};