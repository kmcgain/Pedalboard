#include "pch.h"
#include "function_factory.h"

FunctionFactory::FunctionFactory(LayoutChanger* layoutChanger) {
	this->layoutChanger = layoutChanger;
}

FunctionFactory::~FunctionFactory() {
	Node<Function*>* node = this->functionsCreated.Start();
	while (node != nullptr) {
		delete node->Value;
		node = node->Next;
	}
}

Function* FunctionFactory::LayoutSelect(int layout) {
	return this->store(new LayoutSelectFunction(layout, this->layoutChanger));
}

Function* FunctionFactory::LayoutIncrement() {
	return this->store(new LayoutIncrementFunction(this->layoutChanger));
}

Function* FunctionFactory::LayoutDecrement() {
	return this->store(new LayoutDecrementFunction(this->layoutChanger));
}

Function* FunctionFactory::SceneSelect(int scene) {
	return this->store(new SceneSelectFunction(scene));
}

Function* FunctionFactory::SceneIncrement(int value) {
	return this->store(new SceneIncrementFunction(value));
}

Function* FunctionFactory::SceneDecrement(int value) {
	return this->store(new SceneDecrementFunction(value));
}

Function* FunctionFactory::ExpToggle(int pedal) {
	return this->store(new ExpToggleFunction(pedal));
}

Function* FunctionFactory::TunerToggle() {
	return this->store(new TunerToggleFunction());
}

Function* FunctionFactory::TapTempo() {
	return this->store(new TapTempoFunction());
}

Function* FunctionFactory::PresetIncrement(int value) {
	return this->store(new PresetIncrementFunction(value));
}

Function* FunctionFactory::PresetDecrement(int value) {
	return this->store(new PresetDecrementFunction(value));
}

Function* FunctionFactory::store(Function* fn) {
    this->functionsCreated.Add(fn);
	return fn;
}