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

        void UpdateState(Preset* preset) {
            SceneState* st = static_cast<SceneState*>(this->state);
            st->UpdateState(preset->getSceneName(this->scene), this->scene, preset->getSelectedSceneNumber());
        }
    protected:
        void execute() {
            this->axeController->SendSceneChange(this->scene);
        }

        FunctionState* createState() {
            return new SceneState("", this->scene, this->Type());
        }
};