#pragma once

#include "function/function.h"

class Screen {
public:
	virtual void DisplayFunction(FunctionState* functionState) = 0;
};