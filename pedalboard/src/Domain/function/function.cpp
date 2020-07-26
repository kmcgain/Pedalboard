#include "pch.h"
#include "function.h"

const char* Function::Name() {
    return typeid(*this).name();           
}