#pragma once

#include "function.h"
#include "../axe_controller.h"

class MuteFunction : public Function {
private:
    AxeController* axeController;

public:
    MuteFunction(AxeController* axeController) {
        this->axeController = axeController;
    }

    const char* Name() {
        return "Mute";
    }

    const FunctionType Type() {
        return FunctionType::ftMute;
    }

protected:
    void execute() {
        ToggleFunctionState* st = static_cast<ToggleFunctionState*>(this->state);
        this->axeController->sendMute(st->Current());
        st->Toggle();
    }

    FunctionState* createState() {
        return new ToggleFunctionState(this->Type());
    }
};