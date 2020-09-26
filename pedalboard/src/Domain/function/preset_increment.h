#pragma once

#include "function.h"
#include "../axe_controller.h"
#include "../logger.h"

class PresetIncrementFunction : public Function {
    private:
        char incrementValue;
        AxeController* axeController;

    public:
        PresetIncrementFunction(char incrementValue, AxeController* axeController) {
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
            st->UpdateState(preset->getPresetName(), preset->getPresetNumber());
        }

    protected:
        void execute() {
            PresetState* st = static_cast<PresetState*>(this->state);
            auto newPreset = st->PresetNumber() + this->incrementValue;
            this->axeController->sendPresetChange(newPreset);
            //st->ChangePreset(newPreset);
        }

        FunctionState* createState() {
            return new PresetState("", 1, this->incrementValue, this->Type());
        }
};
