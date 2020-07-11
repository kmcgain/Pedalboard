#pragma once

#include "function.h"

class PresetIncrementFunction : public Function {
    private:
        int incrementValue;

    public:
        PresetIncrementFunction(int incrementValue) {
            this->incrementValue = incrementValue;
        }

        void Execute() {}
};
