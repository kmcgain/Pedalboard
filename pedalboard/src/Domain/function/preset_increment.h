#pragma once

#include "function.h"
#include "../axe_controller.h"
#include "../logger.h"

class PresetIncrementFunction : public Function {
    private:
        char incrementValue;
        AxeController* axeController;

    public:
        PresetIncrementFunction(char incrementValue, AxeController* axeController) {
            this->incrementValue = incrementValue;
            this->axeController = axeController;
        }

        const char* Name() {
            return "PresetIncrement";
        }

        const FunctionType Type() {
            return FunctionType::ftPresetIncrement;
        }


    protected:
        void execute() {
            this->axeController->sendPresetIncrement();
        }

        FunctionState* createState() {
            return new ScalarFunctionState(this->incrementValue, this->Type());
        }
};
