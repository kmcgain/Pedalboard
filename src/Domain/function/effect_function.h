#pragma once


#include "function.h"
#include "../axe_controller.h"

class EffectFunction : public Function {
private:
    AxeController* axeController;
    unsigned short position;
    

public:
    EffectFunction(AxeController* axeController, unsigned short position) {
        this->axeController = axeController;
        this->position = position;
    }


    const char* Name() {
        return "Effect";
    }

    const FunctionType Type() {
        return FunctionType::ftEffect;
    }

    void UpdateState(Preset* preset) {
        EffectState* st = static_cast<EffectState*>(this->state);
        char effectTag[10];
        
        if (preset->getEffectCount() <= this->position) {
            st->UpdateState("", this->position - 1, true);
        }
        else {
            preset->getEffectName(this->position - 1, effectTag, 10);
            auto bypassed = preset->getEffectBypassed(this->position - 1);

            st->UpdateState(effectTag, this->position - 1, bypassed);
        }
    }

protected:
    void execute() {
        EffectState* st = static_cast<EffectState*>(this->state);
        this->axeController->changeEffectStatus(this->position - 1, st->Bypassed());
    }

    FunctionState* createState() {
        return new EffectState("", this->position, this->Type());
    }

};
