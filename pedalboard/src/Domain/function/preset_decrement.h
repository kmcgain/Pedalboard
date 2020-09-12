#pragma once

#include "function.h"
#include "../axe_controller.h"

class PresetDecrementFunction : public Function {
    private:
        char decrementValue;
        AxeController* axeController;

    public:
        PresetDecrementFunction(char decrementValue, AxeController* axeController) {
            this->decrementValue = decrementValue;
            this->axeController = axeController;
        }


        const char* Name() {
            return "PresetDecrement";
        }

        const FunctionType Type() {
            return FunctionType::ftPresetDecrement;
        }


    protected:
        void execute() {
            this->axeController->sendPresetDecrement();
        }

        FunctionState* createState() {
            return new ScalarFunctionState(this->decrementValue, this->Type());
        }

};
