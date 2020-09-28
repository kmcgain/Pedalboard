#pragma once

#include "../function_type.h"
#include "../../logger.h"
#include "../../str_fn.h"

#ifdef ARDUINO
#include <Arduino.h>
#else
#include <cstdio>
#endif

#define UINT_MAX 4294967295
// 32 + null term
#define MAX_SCENE_NAME_LENGTH 33 

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

class PresetState : public ScalarFunctionState {
private:
	char name[MAX_SCENE_NAME_LENGTH];
	unsigned short presetNumber;
	char asdfMsg[50];


	unsigned int nameHash() {
		unsigned int hash = 0;
		if (name == nullptr || name == "")
			return hash;

		int idx = 0;
		while (name[idx] != '\0' && idx < 5) {
			int x = name[idx++] - '0';
			hash = (hash*10) + x;
		}
		
		return hash;
	}

public:
	PresetState(const char* name, unsigned short presetNumber, char relativeChange, FunctionType type) : ScalarFunctionState(relativeChange, type) {
		strTerm(this->name, name, MAX_SCENE_NAME_LENGTH);
		this->presetNumber = presetNumber;
	}

	void UpdateState(const char* name, unsigned short presetNumber) {
		strTerm(this->name, name, MAX_SCENE_NAME_LENGTH);
		this->presetNumber = presetNumber;
	}

	unsigned short PresetNumber() {
		return this->presetNumber;
	}

	const char* PresetName() {
		return this->name;
	}

	void ChangePreset(unsigned short presetNumber) {
		this->presetNumber = presetNumber;
	}

	unsigned int HashCode() {
		
		unsigned int nHash = nameHash();
		unsigned int hash = ScalarFunctionState::HashCode() + this->presetNumber + nHash;
		return hash;
	}
};

class SceneState : public ScalarFunctionState {
private:
	const char* name;
	unsigned short isSelected = false;

	unsigned int compute_hash(const char* s) {
		// will overflow, but chance of conflict low
		const char p = 31;
		unsigned int hash_value = 0;
		unsigned int p_pow = 1;
		unsigned short i = 0;
		while (true) {
			if (s[i] == '\0')
				break;

			hash_value = (hash_value + (s[i++] - 'a' + 1) * p_pow) % UINT_MAX;
			p_pow = (p_pow * p) % UINT_MAX;
		}

		return hash_value;
	}

public:
	SceneState(const char* name, char number, FunctionType type) : ScalarFunctionState(number, type) {
		this->name = name;
	}

	void UpdateState(const char* name, char number, unsigned short selectedScene) {
		this->name = name;
		this->scalar = number;
		this->isSelected = selectedScene == number;
	}

	unsigned int HashCode() {
		// May overflow, but that's ok
		return ScalarFunctionState::HashCode() + this->compute_hash(this->name) + this->isSelected;
	}
};