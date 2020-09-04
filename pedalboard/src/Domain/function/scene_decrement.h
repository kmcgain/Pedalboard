#pragma once

#include "function.h"
#include "../axe_controller.h"

class SceneDecrementFunction : public Function {
    private:
        int decrementValue;
        AxeController* axeController;

    public:
        SceneDecrementFunction(int decrementValue, AxeController* axeController) {
            this->decrementValue = decrementValue;
            this->axeController = axeController;
        }

        const char* Name() {
            return "SceneDecrement";
        }

        const FunctionType Type() {
            return Function::FunctionType::sceneDecrement;
        }

    protected:
        void execute() {
            this->axeController->sendSceneDecrement();
        }
};