#include "pch.h"
#include "function.h"
#include "../logger.h"

//const char* Function::Name() {
//    return typeid(*this).name();           
//}

void Function::Execute() {
	Logger::log(this->Name());
	this->execute();
}