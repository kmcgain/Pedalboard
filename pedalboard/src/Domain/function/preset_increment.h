#pragma once

#include "function.h"
#include "../axe_controller.h"
#include "../logger.h"

class PresetIncrementFunction : public Function {
    private:
        int incrementValue;
        AxeController* axeController;

    public:
        PresetIncrementFunction(int incrementValue, AxeController* axeController) {
            this->incrementValue = incrementValue;
            this->axeController = axeController;
        }

        const char* Name() {
            return "PresetIncrement";
        }

        const FunctionType Type() {
            return Function::FunctionType::presetIncrement;
        }

    protected:
        void execute() {
            this->axeController->sendPresetIncrement();
        }
};
