#ifndef FUNCTION_IMPL_H
#define FUNCTION_IMPL_H

#include "function.h"
#include "layout_changer.h"

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
class SceneSelectFunction : public Function {
    private:
        int scene;

    public:
        SceneSelectFunction(int scene) {
            this->scene = scene;
        }

        void Execute() {}
};
class PresetIncrementFunction : public Function {
    private:
        int incrementValue;

    public:
        PresetIncrementFunction(int incrementValue) {
            this->incrementValue = incrementValue;
        }

        void Execute() {}
};

class PresetDecrementFunction : public Function {
    private:
        int decrementValue;

    public:
        PresetDecrementFunction(int decrementValue) {
            this->decrementValue = decrementValue;
        }

        void Execute() {}
};

class SceneDecrementFunction : public Function {
    private:
        int decrementValue;

    public:
        SceneDecrementFunction(int decrementValue) {
            this->decrementValue = decrementValue;
        }

        void Execute() {}
};
class SceneIncrementFunction : public Function {
    private:
        int incrementValue;

    public:
        SceneIncrementFunction(int incrementValue) {
            this->incrementValue = incrementValue;
        }

        void Execute() {}
};
class ExpToggleFunction : public Function {
    private:
        int pedalNum;

    public:
        ExpToggleFunction(int pedalNum) {
            this->pedalNum = pedalNum;
        }

        void Execute() {}
};
class TunerToggleFunction : public Function {
    public:
        TunerToggleFunction() {
        }

        void Execute() {}
};
class TapTempoFunction : public Function {
    public:
        TapTempoFunction() {
        }

        void Execute() {}
};

#endif