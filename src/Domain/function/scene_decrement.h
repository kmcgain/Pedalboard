#pragma once

#include "function.h"
#include "../axe_controller.h"

class SceneDecrementFunction : public Function {
    private:
        byte decrementValue;
        AxeController* axeController;

    public:
        SceneDecrementFunction(byte decrementValue, AxeController* axeController) {
            this->decrementValue = decrementValue;
            this->axeController = axeController;
        }

        const char* Name() {
            return "SceneDecrement";
        }

        const FunctionType Type() {
            return FunctionType::ftSceneDecrement;
        }

    protected:
        void execute() {
            this->axeController->sendSceneDecrement();
        }

        FunctionState* createState() {
            return new ScalarFunctionState(this->decrementValue, this->Type());
        }
};