#ifndef FUNCTION_H
#define FUNCTION_H



class Function {   
    public:
        enum class FunctionType
        {
            layoutIncrement,
            layoutDecrement,
            presetIncrement,
            presetDecrement,
            layoutSelect,
            sceneIncrement,
            sceneDecrement,
            sceneSelect,
            tapTempo,
            tunerToggle,
            expToggle
        };

        virtual void Execute();
        virtual const char* Name() = 0;
        virtual const FunctionType Type() = 0;

    protected:
        virtual void execute() = 0;
};

#endif