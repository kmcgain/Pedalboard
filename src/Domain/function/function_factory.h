#pragma once

#include "function.h"
#include "all_functions.h"
#include "../layout_changer.h"

#include "linked_list.h"
#include "linked_list.cpp"

#include "../axe_controller.h"
#include "../expression.h"

class FunctionFactory {
private:
	LayoutChanger* layoutChanger;
	LinkedList<Function*> functionsCreated;
	AxeController* axeController;

public:
	FunctionFactory(LayoutChanger* layoutChanger, AxeController* axeController);
	~FunctionFactory();
	virtual Function* LayoutSelect(char layout);

	virtual Function* LayoutIncrement();
	virtual Function* LayoutDecrement();
	virtual Function* SceneSelect(char scene);
	virtual Function* SceneIncrement(char value);
	virtual Function* SceneDecrement(char value);
	virtual Function* ExpToggle(char pedal, short* extControls, short numControls, Expression* exp);
	virtual Function* TunerToggle();
	virtual Function* TapTempo();
	virtual Function* PresetIncrement(char value);
	virtual Function* PresetDecrement(char value);
	virtual Function* PresetDisplay();
	virtual Function* PresetFullSelect(unsigned short buttonNum, PresetSelector* PresetSelector);
	virtual Function* Mute();
	virtual Function* Effect(unsigned short position);

private:
	Function* store(Function* fn);
};