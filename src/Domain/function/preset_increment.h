#pragma once

#include "function.h"
#include "../axe_controller.h"
#include "../logger.h"

class PresetIncrementFunction : public Function {
    private:
        byte incrementValue;
        AxeController* axeController;

    public:
        PresetIncrementFunction(byte incrementValue, AxeController* axeController) {
            this->incrementValue = incrementValue;
            this->axeController = axeController;
        }

        const char* Name() {
            return "PresetIncrement";
        }

        const FunctionType Type() {
            return FunctionType::ftPresetIncrement;
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
            st->ChangePreset(st->PresetNumber() + this->incrementValue);
            if (this->incrementValue == 1) {
                this->axeController->sendPresetIncrement();
            }
            else {
                this->axeController->sendPresetChange(st->PresetNumber());
            }
        }

        FunctionState* createState() {
            return new PresetState("", 1, this->incrementValue, this->Type());
        }
};
