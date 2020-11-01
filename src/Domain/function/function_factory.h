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

	Function* LayoutIncrement();
	Function* LayoutDecrement();
	Function* SceneSelect(char scene);
	Function* SceneIncrement(char value);
	Function* SceneDecrement(char value);
	Function* ExpToggle(char pedal, short* extControls, short numControls, Expression* exp);
	Function* TunerToggle();
	Function* TapTempo();
	Function* PresetIncrement(char value);
	Function* PresetDecrement(char value);
	Function* PresetDisplay();
	Function* Mute();
	Function* Effect(unsigned short position);

private:
	Function* store(Function* fn);
};