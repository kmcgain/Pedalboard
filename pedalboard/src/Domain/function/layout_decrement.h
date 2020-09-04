#pragma once

#include "function.h"
#include "../layout_changer.h"

class LayoutDecrementFunction : public Function {
    private:
        LayoutChanger* layoutChanger;

    public:
        LayoutDecrementFunction(LayoutChanger* layoutChanger) {
            this->layoutChanger = layoutChanger;
        }

        const char* Name() {
            return "LayoutDecrement";
        }

        const FunctionType Type() {
            return Function::FunctionType::layoutDecrement;
        }

protected:

    void execute() {
        this->layoutChanger->IncrementLayout(-1);
    }
};