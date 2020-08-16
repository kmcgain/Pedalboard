#include "pch.h"
#include "function.h"
#include "../logger.h"

void Function::Execute() {
	Logger::log(this->Name());
	Logger::log("\n");
	this->execute();
}