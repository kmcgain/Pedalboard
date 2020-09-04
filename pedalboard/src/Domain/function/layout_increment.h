#pragma once

#include "function.h"
#include "../layout_changer.h"

class LayoutIncrementFunction : public Function {
    private:
        LayoutChanger* layoutChanger;

    public:
        LayoutIncrementFunction(LayoutChanger* layoutChanger) {
            this->layoutChanger = layoutChanger;
        }

        const char* Name() {
            return "LayoutIncrement";
        }

        const FunctionType Type() {
            return Function::FunctionType::layoutIncrement;
        }

    protected:

        void execute() {
            this->layoutChanger->IncrementLayout(1);
        }

};