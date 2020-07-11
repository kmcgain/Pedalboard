#pragma once

#include "function.h"

class SceneIncrementFunction : public Function {
    private:
        int incrementValue;

    public:
        SceneIncrementFunction(int incrementValue) {
            this->incrementValue = incrementValue;
        }

        void Execute() {}
};