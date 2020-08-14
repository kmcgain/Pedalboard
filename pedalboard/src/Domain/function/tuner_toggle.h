#pragma once

#include "function.h"

class TunerToggleFunction : public Function {
    public:
        TunerToggleFunction() {
        }

        const char* Name() {
            return "TunerToggle";
        }

    protected:
        void execute() {}
};