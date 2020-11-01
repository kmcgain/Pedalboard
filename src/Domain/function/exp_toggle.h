#pragma once

#include "function.h"
#include "../expression.h"

class ExpToggleFunction : public Function {
    private:
        short pedalNum;
        Expression* exp;
        short* extControls;
        short numPedals;

    public:
        ExpToggleFunction(short pedalNum, short extControls[], short numControls, Expression* exp) {
            this->pedalNum = pedalNum;
            this->exp = exp;
            this->numPedals = numControls;
            this->extControls = (short*)malloc(sizeof(short)*this->numPedals);
            memcpy(this->extControls, extControls, sizeof(short)*this->numPedals);
        }

        void execute() {
            ExpressionFunctionState* st = static_cast<ExpressionFunctionState*>(this->state);
            st->Switch();
            this->exp->ChangeExp(st->Selected());
        }
        
        const char* Name() {
            return "ExpToggle";
        }

        const FunctionType Type() {
            return FunctionType::ftExpToggle;
        }

protected:


    FunctionState* createState() {     
        return new ExpressionFunctionState(pedalNum, extControls, numPedals, this->Type());
    }
};