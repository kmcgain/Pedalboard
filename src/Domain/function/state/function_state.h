#pragma once

#include "../function_type.h"
#include "../../logger.h"
#include "../../str_fn.h"

#include "../../preset_selector.h"
#include "../../axe_controller.h"

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


	unsigned int str_hash(const char* s) {
		// will overflow, but chance of conflict low
		const char p = 31;
		unsigned int hash_value = 0;
		unsigned int p_pow = 1;
		unsigned short i = 0;
		while (true) {
			if (s == nullptr || s[i] == '\0')
				break;

			hash_value = (hash_value + (s[i++] - 'a' + 1) * p_pow) % UINT_MAX;
			p_pow = (p_pow * p) % UINT_MAX;
		}

		return hash_value;
	}

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
		return (UINT_MAX-1) / this->type;
	}
};

class ExpressionFunctionState : public FunctionState {
protected:
	short selectedExt, totalPedals;
	short* pedals;
	
public:
	ExpressionFunctionState(short selectedExt, short pedals[], short totalPedals, FunctionType type) : FunctionState(type) {
		this->selectedExt = selectedExt;
		this->pedals = (short*)malloc(totalPedals * sizeof(short));
		memcpy(this->pedals, pedals, totalPedals * sizeof(short));
		this->totalPedals = totalPedals;
	}

	unsigned int HashCode() {
		// Won't clash with different function type hashcodes
		return (UINT_MAX - 1) / this->type + (int)selectedExt;
	}

	void Switch() {
		this->selectedExt++;
		if (this->selectedExt > totalPedals)
			this->selectedExt = 1;		
	}

	short Selected() {
		return this->selectedExt;
	}

	short* Pedals() {
		return this->pedals;
	}

	short NumOfPedals() {
		return this->totalPedals;
	}
};

class ToggleFunctionState : public FunctionState {
protected:
	bool toggle = true;

public:
	ToggleFunctionState(FunctionType type) : FunctionState(type) {
	}

	unsigned int HashCode() {
		// Won't clash with different function type hashcodes
		return (UINT_MAX - 1) / this->type + (int)toggle;
	}

	void Toggle() {
		toggle = !toggle;
	}

	bool Current() {
		return toggle;
	}
};

class ScalarFunctionState : public FunctionState {
protected:
	byte scalar;

public:
	ScalarFunctionState(byte scalar, FunctionType type) : FunctionState(type) {
		this->scalar = scalar;
	}

	byte Scalar() {
		return this->scalar;
	}

	unsigned int HashCode() {
		// Won't clash with different function type hashcodes
		return (UINT_MAX / this->type) + scalar; 
	}
};

class PresetFullSelectState : public FunctionState {
private:
	PresetSelector* presetSelector;
	AxeController* axeController;

public:
	PresetFullSelectState(PresetSelector* presetSelector, AxeController* axeController) 
	: FunctionState(FunctionType::ftPresetFullSelect) {
		this->presetSelector = presetSelector;
		this->axeController = axeController;
	}

	PresetSelector* GetPresetSelector() {
		return presetSelector;
	}

	PresetNames* AllPresetNames() {
		return axeController->presetNames();
	}

	int CurrentPresetNumber() {
		return axeController->currentPresetNumber();
	}

	unsigned int HashCode() {
		// We hide the different attributes within the 1 int. 
		// 8 bits to cover 0-511 so we need 17 bits + 8 bits for the page number. - will fit in 4 bytes
		unsigned int hash = (GetPresetSelector()->SelectedPage() << 18) + ((presetSelector->Active ? 1 : 0) << 17) + (presetSelector->Max << 9) + (presetSelector->Min << 1);
		return hash;
	}
};

class PresetState : public ScalarFunctionState {
private:
	char name[MAX_SCENE_NAME_LENGTH];
	unsigned short presetNumber;

public:
	PresetState(const char* name, unsigned short presetNumber, byte relativeChange, FunctionType type) : ScalarFunctionState(relativeChange, type) {
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
		unsigned int hash = ScalarFunctionState::HashCode() + this->presetNumber + this->str_hash(this->name);
		return hash;
	}
};

class SceneState : public ScalarFunctionState {
private:
	char name[MAX_SCENE_NAME_LENGTH];
	unsigned short isSelected = false;

public:
	SceneState(const char* name, byte number, FunctionType type) : ScalarFunctionState(number, type) {
		strTerm(this->name, name, MAX_SCENE_NAME_LENGTH);
	}

	void UpdateState(const char* name, byte number, unsigned short selectedScene) {
		strTerm(this->name, name, MAX_SCENE_NAME_LENGTH);
		this->scalar = number;
		this->isSelected = selectedScene == number;
	}

	unsigned int HashCode() {
		// May overflow, but that's ok
		auto nmHash = this->str_hash(this->name);
		return ScalarFunctionState::HashCode() + nmHash + this->isSelected;
	}
};


class EffectState : public ScalarFunctionState {
private:
	char name[10];
	bool bypassed = false;

public:
	EffectState(const char* name, byte number, FunctionType type) : ScalarFunctionState(number, type) {
		strTerm(this->name, name, 10);
	}

	void UpdateState(const char* name, byte effectNum, bool bypassed) {
		strTerm(this->name, name, 10);
		this->scalar = effectNum;
		this->bypassed = bypassed;
	}

	bool Bypassed() {
		return this->bypassed;
	}

	const char* Name() {
		return name;
	}

	unsigned int HashCode() {
		// May overflow, but that's ok
		return ScalarFunctionState::HashCode() + this->bypassed + this->str_hash(this->name);
	}
};