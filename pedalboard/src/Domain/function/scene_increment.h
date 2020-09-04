#pragma once

#include "function.h"
#include "../axe_controller.h"

class SceneIncrementFunction : public Function {
    private:
        int incrementValue;
        AxeController* axeController;

    public:
        SceneIncrementFunction(int incrementValue, AxeController* axeController) {
            this->incrementValue = incrementValue;
            this->axeController = axeController;
        }

        const char* Name() {
            return "SceneIncrement";
        }

        const FunctionType Type() {
            return Function::FunctionType::sceneIncrement;
        }
    protected:
        void execute() {
            this->axeController->sendSceneIncrement();
        }
};