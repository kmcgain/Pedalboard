#pragma once

#include "function.h"
#include "all_functions.h"
#include "../layout_changer.h"

#include "linked_list.h"
#include "linked_list.cpp"

#include "../axe_controller.h"

class FunctionFactory {
private:
	LayoutChanger* layoutChanger;
	LinkedList<Function*> functionsCreated;
	AxeController* axeController;

public:
	FunctionFactory(LayoutChanger* layoutChanger, AxeController* axeController);
	~FunctionFactory();
	virtual Function* LayoutSelect(int layout);

	Function* LayoutIncrement();
	Function* LayoutDecrement();
	Function* SceneSelect(int scene);
	Function* SceneIncrement(int value);
	Function* SceneDecrement(int value);
	Function* ExpToggle(int pedal);
	Function* TunerToggle();
	Function* TapTempo();
	Function* PresetIncrement(int value);
	Function* PresetDecrement(int value);

private:
	Function* store(Function* fn);
};