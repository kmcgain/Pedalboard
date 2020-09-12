#pragma once

#include "function.h"

class ExpToggleFunction : public Function {
    private:
        char pedalNum;

    public:
        ExpToggleFunction(char pedalNum) {
            this->pedalNum = pedalNum;
        }

        void execute() {}
        
        const char* Name() {
            return "ExpToggle";
        }

        const FunctionType Type() {
            return FunctionType::ftExpToggle;
        }

protected:


    FunctionState* createState() {
        return new FunctionState(this->Type());
    }
};