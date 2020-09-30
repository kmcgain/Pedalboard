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

        void UpdateState(Preset* preset) {
            PresetState* st = static_cast<PresetState*>(this->state);
            char presetName[MAX_SCENE_NAME_LENGTH];
            preset->getPresetName(presetName, MAX_SCENE_NAME_LENGTH);
            st->UpdateState(presetName, preset->getPresetNumber());
        }

    protected:
        void execute() {
            PresetState* st = static_cast<PresetState*>(this->state);
            auto newPreset = st->PresetNumber() - this->decrementValue;
            this->axeController->sendPresetChange(newPreset);
            //st->ChangePreset(newPreset);
        }

        FunctionState* createState() {
            return new PresetState("", 1, this->decrementValue, this->Type());
        }

};
