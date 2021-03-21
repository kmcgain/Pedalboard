#pragma once

#include "function.h"
#include "../axe_controller.h"
#include "../logger.h"

#include "../preset_selector.h"

class PresetFullSelectFunction : public Function {
    private:
        AxeController* axeController;
        byte buttonNum;
        PresetSelector* presetSelector;
        LayoutChanger* layoutChanger;

    public:
        PresetFullSelectFunction(byte buttonNum, AxeController* axeController, PresetSelector* presetSelector, LayoutChanger* layoutChanger) {
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
            const int pageDownButtonNum = 3;
            const int pageUpButtonNum = 4;

            Logger::log("\nExec: PresetFullSelect");
            if (this->buttonNum == backButtonNum) {
                Logger::log("\nBack button");
                if (presetSelector->IsLowestLevel()) {
                    presetSelector->PageReset();
                    layoutChanger->PresetSelect();
                    return;
                }
                presetSelector->Reset();
                return;
            } 

            PresetFullSelectState* st = static_cast<PresetFullSelectState*>(this->state);
            if (this->buttonNum == pageDownButtonNum)
            {
                Logger::log("\nPage down");
                presetSelector->PageDown();
                return;
            }
            if (this->buttonNum == pageUpButtonNum)
            {
                Logger::log("\nPage up");
                presetSelector->PageUp();
                return;
            }

            this->axeController->sendPresetChange(presetSelector->NumberForPageAndScreen(this->buttonNum, st->CurrentPresetNumber()));
            this->presetSelector->Reset();
            this->presetSelector->PageReset();
            this->layoutChanger->PresetSelect();
        }

        FunctionState* createState() {
            return new PresetFullSelectState(this->presetSelector, this->axeController);
        }
};
