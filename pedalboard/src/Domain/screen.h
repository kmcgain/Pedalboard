#pragma once

#include "function/function.h"

class Screen {
public:
	virtual void DisplayFunction(const Function::FunctionType functionType) = 0;
};