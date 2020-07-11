#pragma once

#include "function.h"

class SceneSelectFunction : public Function {
    private:
        int scene;

    public:
        SceneSelectFunction(int scene) {
            this->scene = scene;
        }

        void Execute() {}
};