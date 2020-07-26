#ifndef FUNCTION_H
#define FUNCTION_H

class Function {   
    public:
        virtual void Execute() = 0;
        virtual const char* Name();
};

#endif