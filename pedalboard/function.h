#ifndef FUNCTION_H
#define FUNCTION_H

class Function {    
};

class LayoutSelectFunction : public Function {
    private:
        int layout;

    public:
        LayoutSelectFunction(int layout) {
            this->layout = layout;
        }
};

class LayoutIncrementFunction : public Function {};
class LayoutDecrementFunction : public Function {};
class SceneSelectFunction : public Function {
    private:
        int scene;

    public:
        SceneSelectFunction(int scene) {
            this->scene = scene;
        }
};
class PresetIncrementFunction : public Function {
    private:
        int incrementValue;

    public:
        PresetIncrementFunction(int incrementValue) {
            this->incrementValue = incrementValue;
        }
};

class PresetDecrementFunction : public Function {
    private:
        int decrementValue;

    public:
        PresetDecrementFunction(int decrementValue) {
            this->decrementValue = decrementValue;
        }
};

class SceneDecrementFunction : public Function {
    private:
        int decrementValue;

    public:
        SceneDecrementFunction(int decrementValue) {
            this->decrementValue = decrementValue;
        }
};
class SceneIncrementFunction : public Function {
    private:
        int incrementValue;

    public:
        SceneIncrementFunction(int incrementValue) {
            this->incrementValue = incrementValue;
        }
};
class ExpToggleFunction : public Function {
    private:
        int pedalNum;

    public:
        ExpToggleFunction(int pedalNum) {
            this->pedalNum = pedalNum;
        }
};
class TunerToggleFunction : public Function {
    public:
        TunerToggleFunction() {
        }
};
class TapTempoFunction : public Function {
    public:
        TapTempoFunction() {
        }
};
#endif