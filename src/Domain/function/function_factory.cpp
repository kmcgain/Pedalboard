#include "pch.h"
#include "function_factory.h"

FunctionFactory::FunctionFactory(LayoutChanger* layoutChanger, AxeController* axeController) {
	this->layoutChanger = layoutChanger;
	this->axeController = axeController;
}

FunctionFactory::~FunctionFactory() {
	Node<Function*>* node = this->functionsCreated.Start();
	while (node != nullptr) {
		delete node->Value;
		node = node->Next;
	}
}

Function* FunctionFactory::LayoutSelect(char layout) {
	return this->store(new LayoutSelectFunction(layout, this->layoutChanger));
}

Function* FunctionFactory::LayoutIncrement() {
	return this->store(new LayoutIncrementFunction(this->layoutChanger));
}

Function* FunctionFactory::LayoutDecrement() {
	return this->store(new LayoutDecrementFunction(this->layoutChanger));
}

Function* FunctionFactory::SceneSelect(char scene) {
	return this->store(new SceneSelectFunction(scene, this->axeController));
}

Function* FunctionFactory::SceneIncrement(char value) {
	return this->store(new SceneIncrementFunction(value, this->axeController));
}

Function* FunctionFactory::SceneDecrement(char value) {
	return this->store(new SceneDecrementFunction(value, this->axeController));
}

Function* FunctionFactory::ExpToggle(char pedal) {
	return this->store(new ExpToggleFunction(pedal));
}

Function* FunctionFactory::TunerToggle() {
	return this->store(new TunerToggleFunction(this->axeController));
}

Function* FunctionFactory::TapTempo() {
	return this->store(new TapTempoFunction(this->axeController));
}

Function* FunctionFactory::PresetIncrement(char value) {
	return this->store(new PresetIncrementFunction(value, this->axeController));
}

Function* FunctionFactory::PresetDecrement(char value) {
	return this->store(new PresetDecrementFunction(value, this->axeController));
}

Function* FunctionFactory::PresetDisplay() {
	return this->store(new PresetDisplayFunction(this->axeController));
}

Function* FunctionFactory::Mute() {
	return this->store(new MuteFunction(this->axeController));
}

Function* FunctionFactory::Effect(unsigned short position) {
	return this->store(new EffectFunction(this->axeController, position));
}

Function* FunctionFactory::store(Function* fn) {
	fn->Init();
    this->functionsCreated.Add(fn);
	return fn;
}