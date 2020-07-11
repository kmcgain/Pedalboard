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

    void Execute() {
        this->layoutChanger->IncrementLayout(1);
    }
};