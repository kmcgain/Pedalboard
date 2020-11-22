#pragma once

#include "function.h"
#include "../axe_controller.h"
#include "../logger.h"

#include "../preset_selector.h"

class PresetFullSelectFunction : public Function {
    private:
        AxeController* axeController;
        char buttonNum;
        PresetSelector* presetSelector;
        LayoutChanger* layoutChanger;

    public:
        PresetFullSelectFunction(char buttonNum, AxeController* axeController, PresetSelector* presetSelector, LayoutChanger* layoutChanger) {
            this->buttonNum = buttonNum;
            this->axeController = axeController;
            this->presetSelector = presetSelector;
            this->layoutChanger = layoutChanger;
        }

        const char* Name() {
            return "PresetFullSelect";
        }

        const FunctionType Type() {
            return FunctionType::ftPresetFullSelect;
        }

    protected:
        void execute() {
            const int backButtonNum = 14;

            if (this->buttonNum == backButtonNum) {
                if (presetSelector->IsLowestLevel()) {
                    layoutChanger->PresetSelect();
                    return;
                }
                presetSelector->Reset();
                return;
            } 

            presetSelector->Expand(this->buttonNum);  
            auto maxLevelRequired = 2;
            if (presetSelector->Min == presetSelector->Max) {
                this->axeController->sendPresetChange(presetSelector->Min);
                this->presetSelector->Reset();
                this->layoutChanger->PresetSelect();
                return;
            }
        }

        FunctionState* createState() {
            return new PresetFullSelectState(this->presetSelector);
        }
};
