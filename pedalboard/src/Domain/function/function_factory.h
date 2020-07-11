#pragma once

#include "function.h"
#include "all_functions.h"
#include "../layout_changer.h"

#include "linked_list.h"

class FunctionFactory {
private:
	LayoutChanger* layoutChanger;
	LinkedList<Function*> functionsCreated;

public:
	FunctionFactory(LayoutChanger* layoutChanger);
	~FunctionFactory();
	virtual Function* LayoutSelect(int layout);

	Function* FunctionFactory::LayoutIncrement();
	Function* FunctionFactory::LayoutDecrement();
	Function* FunctionFactory::SceneSelect(int scene);
	Function* FunctionFactory::SceneIncrement(int value);
	Function* FunctionFactory::SceneDecrement(int value);
	Function* FunctionFactory::ExpToggle(int pedal);
	Function* FunctionFactory::TunerToggle();
	Function* FunctionFactory::TapTempo();
	Function* FunctionFactory::PresetIncrement(int value);
	Function* FunctionFactory::PresetDecrement(int value);

private:
	Function* store(Function* fn);
};