#pragma once


#include "function.h"
#include "../axe_controller.h"

class PresetDisplayFunction : public Function {
private:
    AxeController* axeController;

public:
    PresetDisplayFunction(AxeController* axeController) {
        this->axeController = axeController;
    }


    const char* Name() {
        return "PresetDisplay";
    }

    const FunctionType Type() {
        return FunctionType::ftPresetDisplay;
    }

    void UpdateState(Preset* preset) {
        PresetState* st = static_cast<PresetState*>(this->state);
        char presetName[MAX_SCENE_NAME_LENGTH];
        preset->getPresetName(presetName, MAX_SCENE_NAME_LENGTH);
        st->UpdateState(presetName, preset->getPresetNumber());
    }

protected:
    void execute() {
        // no-op
    }

    FunctionState* createState() {
        return new PresetState("", 1, 0, this->Type());
    }

};
