#pragma once

#include "function.h"
#include "../layout_changer.h"

class LayoutSelectFunction : public Function {
    private:
        byte layout;
        LayoutChanger* layoutChanger;

    public:
        LayoutSelectFunction(byte layout, LayoutChanger* layoutChanger) {
            this->layout = layout;
            this->layoutChanger = layoutChanger;
        }

        const char* Name() {
            return "layoutSelect";
        }

        const FunctionType Type() {
            return FunctionType::ftLayoutSelect;
        }

    protected:
        void execute() {
            this->layoutChanger->SelectLayout(this->layout);
        }


        FunctionState* createState() {
            return new ScalarFunctionState(this->layout, this->Type());
        }
};
