#pragma once

#include "function.h"

#include "../axe_controller.h"

class SceneSelectFunction : public Function {
    private:
        char scene;
        AxeController* axeController;

    public:
        SceneSelectFunction(char scene, AxeController* axeController) {
            this->scene = scene;
            this->axeController = axeController;
        }

        const char* Name() {
            return "SceneSelect";
        }

        const FunctionType Type() {
            return FunctionType::ftSceneSelect;
        }
    protected:
        void execute() {
            this->axeController->SendSceneChange(this->scene);
        }

        FunctionState* createState() {
            return new ScalarFunctionState(this->scene, this->Type());
        }
};