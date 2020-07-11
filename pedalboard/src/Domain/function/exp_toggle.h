#pragma once

#include "function.h"

class ExpToggleFunction : public Function {
    private:
        int pedalNum;

    public:
        ExpToggleFunction(int pedalNum) {
            this->pedalNum = pedalNum;
        }

        void Execute() {}
};