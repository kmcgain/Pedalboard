#ifndef FUNCTION_H
#define FUNCTION_H

#include "function_type.h"
#include "state/function_state.h"
#include "../preset.h"

class Function {   
    public:            
        virtual void Execute();
        virtual const char* Name() = 0;
        virtual const FunctionType Type() = 0;
        FunctionState* State();
        virtual void UpdateState(Preset* preset);
        void Init();

    protected:
        virtual FunctionState* createState() = 0;
        virtual void execute() = 0;
        FunctionState* state;
};

#endif