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

    void Execute() {
        this->layoutChanger->IncrementLayout(-1);
    }
};