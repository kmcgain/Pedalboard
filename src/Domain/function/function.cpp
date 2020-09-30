#include "pch.h"
#include "function.h"
#include "../logger.h"

void Function::Execute() {
	this->execute();
}

void Function::Init() {
	this->state = this->createState();
}

FunctionState* Function::State() {
	return this->state;
}

void Function::UpdateState(Preset* preset) {}