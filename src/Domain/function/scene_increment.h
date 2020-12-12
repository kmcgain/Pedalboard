#pragma once

#include "function.h"
#include "../axe_controller.h"

class SceneIncrementFunction : public Function {
    private:
        byte incrementValue;
        AxeController* axeController;

    public:
        SceneIncrementFunction(byte incrementValue, AxeController* axeController) {
            this->incrementValue = incrementValue;
            this->axeController = axeController;
        }

        const char* Name() {
            return "SceneIncrement";
        }

        const FunctionType Type() {
            return FunctionType::ftSceneIncrement;
        }
    protected:
        void execute() {
            this->axeController->sendSceneIncrement();
        }

        FunctionState* createState() {
            return new ScalarFunctionState(this->incrementValue, this->Type());
        }
};
