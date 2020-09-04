#pragma once

#include "function.h"

class ExpToggleFunction : public Function {
    private:
        int pedalNum;

    public:
        ExpToggleFunction(int pedalNum) {
            this->pedalNum = pedalNum;
        }

        void execute() {}
        
        const char* Name() {
            return "ExpToggle";
        }

        const FunctionType Type() {
            return Function::FunctionType::expToggle;
        }
};