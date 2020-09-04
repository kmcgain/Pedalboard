#pragma once

#include "function.h"
#include "../axe_controller.h"

class TunerToggleFunction : public Function {
    private:
        AxeController* axeController;

    public:
        TunerToggleFunction(AxeController* axeController) {
            this->axeController = axeController;
        }

        const char* Name() {
            return "TunerToggle";
        }

        const FunctionType Type() {
            return Function::FunctionType::tunerToggle;
        }

    protected:
        void execute() {
            this->axeController->toggleTuner();
        }
};