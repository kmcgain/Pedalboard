#ifndef FUNCTION_H
#define FUNCTION_H

class Function {   
    public:
        virtual void Execute();
        virtual const char* Name() = 0;

    protected:
        virtual void execute() = 0;
};

#endif