#pragma once

#include "function.h"

class SceneDecrementFunction : public Function {
    private:
        int decrementValue;

    public:
        SceneDecrementFunction(int decrementValue) {
            this->decrementValue = decrementValue;
        }

        const char* Name() {
            return "SceneDecrement";
        }
    protected:
        void execute() {}
};