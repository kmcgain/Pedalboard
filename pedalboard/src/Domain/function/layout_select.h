#pragma once

#include "function.h"
#include "../layout_changer.h"

class LayoutSelectFunction : public Function {
    private:
        int layout;
        LayoutChanger* layoutChanger;

    public:
        LayoutSelectFunction(int layout, LayoutChanger* layoutChanger) {
            this->layout = layout;
            this->layoutChanger = layoutChanger;
        }

        void Execute() {
            this->layoutChanger->SelectLayout(this->layout);
        }
};
