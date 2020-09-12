#pragma once

#include "../function_type.h"

class FunctionState {
protected:
	FunctionType type;

public:
	FunctionState(FunctionType type) {
		this->type = type;
	}
	virtual ~FunctionState() {}

	FunctionType Type() {
		return this->type;
	}
};

class ScalarFunctionState : public FunctionState {
private:
	char scalar;

public:
	ScalarFunctionState(char scalar, FunctionType type) : FunctionState(type) {
		this->scalar = scalar;
	}

	char Scalar() {
		return this->scalar;
	}
};
