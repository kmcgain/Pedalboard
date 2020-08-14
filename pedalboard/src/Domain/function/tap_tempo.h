#pragma once

#include "function.h"

class TapTempoFunction : public Function {
    public:
        TapTempoFunction() {
        }

        const char* Name() {
            return "TapTempo";
        }

    protected:
        void execute() {}
};