#pragma once

#include "function.h"

#include "axe_controller.h"

class SceneSelectFunction : public Function {
    private:
        int scene;
        AxeController* axeController;

    public:
        SceneSelectFunction(int scene, AxeController* axeController) {
            this->scene = scene;
            this->axeController = axeController;
        }

        void Execute() {
            this->axeController->SendSceneChange(this->scene);
        }
};