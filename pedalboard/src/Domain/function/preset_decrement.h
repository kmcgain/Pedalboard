#pragma once

#include "function.h"

class PresetDecrementFunction : public Function {
    private:
        int decrementValue;

    public:
        PresetDecrementFunction(int decrementValue) {
            this->decrementValue = decrementValue;
        }


        const char* Name() {
            return "PresetDecrement";
        }

    protected:
        void execute() {}
};
