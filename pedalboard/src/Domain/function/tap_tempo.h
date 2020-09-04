#pragma once

#include "function.h"
#include "../axe_controller.h"

class TapTempoFunction : public Function {
    private:
        AxeController* axeController;

    public:
        TapTempoFunction(AxeController* axeController) {
            this->axeController = axeController;
        }

        const char* Name() {
            return "TapTempo";
        }

        const FunctionType Type() {
            return Function::FunctionType::tapTempo;
        }

    protected:
        void execute() {
            this->axeController->sendTap();
        }
};