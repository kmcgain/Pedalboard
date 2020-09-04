#pragma once

#include "function.h"
#include "../axe_controller.h"

class PresetDecrementFunction : public Function {
    private:
        int decrementValue;
        AxeController* axeController;

    public:
        PresetDecrementFunction(int decrementValue, AxeController* axeController) {
            this->decrementValue = decrementValue;
            this->axeController = axeController;
        }


        const char* Name() {
            return "PresetDecrement";
        }

        const FunctionType Type() {
            return Function::FunctionType::presetDecrement;
        }

    protected:
        void execute() {
            this->axeController->sendPresetDecrement();
        }
};
