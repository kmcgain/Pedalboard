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

Function* FunctionFactory::LayoutSelect(byte layout) {
	return this->store(new LayoutSelectFunction(layout, this->layoutChanger));
}

Function* FunctionFactory::LayoutIncrement() {
	return this->store(new LayoutIncrementFunction(this->layoutChanger));
}

Function* FunctionFactory::LayoutDecrement() {
	return this->store(new LayoutDecrementFunction(this->layoutChanger));
}

Function* FunctionFactory::SceneSelect(byte scene) {
	return this->store(new SceneSelectFunction(scene, this->axeController));
}

Function* FunctionFactory::SceneIncrement(byte value) {
	return this->store(new SceneIncrementFunction(value, this->axeController));
}

Function* FunctionFactory::SceneDecrement(byte value) {
	return this->store(new SceneDecrementFunction(value, this->axeController));
}

Function* FunctionFactory::ExpToggle(byte pedal, short extControls[], short numControls, Expression* exp) {
	return this->store(new ExpToggleFunction(pedal, extControls, numControls, exp));
}

Function* FunctionFactory::TunerToggle() {
	return this->store(new TunerToggleFunction(this->axeController));
}

Function* FunctionFactory::TapTempo() {
	return this->store(new TapTempoFunction(this->axeController));
}

Function* FunctionFactory::PresetIncrement(byte value) {
	return this->store(new PresetIncrementFunction(value, this->axeController));
}

Function* FunctionFactory::PresetDecrement(byte value) {
	return this->store(new PresetDecrementFunction(value, this->axeController));
}

Function* FunctionFactory::PresetDisplay() {
	return this->store(new PresetDisplayFunction(this->axeController, this->layoutChanger));
}

Function* FunctionFactory::Mute() {
	return this->store(new MuteFunction(this->axeController));
}

Function* FunctionFactory::Effect(unsigned short position) {
	return this->store(new EffectFunction(this->axeController, position));
}

Function* FunctionFactory::PresetFullSelect(unsigned short buttonNum, PresetSelector* presetSelector) {
	return this->store(new PresetFullSelectFunction(buttonNum, this->axeController, presetSelector, this->layoutChanger));
}

Function* FunctionFactory::store(Function* fn) {
	fn->Init();
    this->functionsCreated.Add(fn);
	return fn;
}