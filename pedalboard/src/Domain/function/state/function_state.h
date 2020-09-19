#pragma once

#include "../function_type.h"

#define UINT_MAX 4294967295

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

	virtual unsigned int HashCode() {
		// 4billion sliced into sections per the total number of types
		return UINT_MAX / this->type;
	}
};

class ScalarFunctionState : public FunctionState {
protected:
	char scalar;

public:
	ScalarFunctionState(char scalar, FunctionType type) : FunctionState(type) {
		this->scalar = scalar;
	}

	char Scalar() {
		return this->scalar;
	}

	unsigned int HashCode() {
		// Won't clash with different function type hashcodes
		return (UINT_MAX / this->type) + scalar; 
	}
};


class SceneState : public ScalarFunctionState {
private:
	const char* name;


	unsigned int compute_hash(const char* s) {
		// will overflow, but chance of conflict low
		const int p = 31;
		const int m = UINT_MAX;
		unsigned int hash_value = 0;
		unsigned int p_pow = 1;
		unsigned short i = 0;
		while (true) {
			if (s[i] == '\0')
				break;

			hash_value = (hash_value + (s[i++] - 'a' + 1) * p_pow) % m;
			p_pow = (p_pow * p) % m;
		}

		return hash_value;
	}

public:
	SceneState(const char* name, char number, FunctionType type) : ScalarFunctionState(number, type) {
		this->name = name;
	}

	void UpdateState(const char* name, char number) {
		this->name = name;
		this->scalar = number;
	}

	unsigned int HashCode() {
		// May overflow, but that's ok
		return ScalarFunctionState::HashCode() + this->compute_hash(this->name);
	}
};