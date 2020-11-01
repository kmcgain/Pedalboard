#ifndef LAYOUT_MANAGER_H
#define LAYOUT_MANAGER_H

#include "layout.h"
#include "function/function.h"
#include "button.h"
#include "layout_changer.h"
#include "function/function_factory.h"
#include "screen.h"
#include "screen_factory.h"

class LayoutManager {
    private: 
        Layout** layouts;
        Layout* activeLayout;
        Button*** buttons;
        Screen*** screens;
        Function* functions[33];
        char layoutNumber;
        LayoutChanger* layoutChanger;
        FunctionFactory* functionFactory;
        ScreenFactory* screenFactory;
        Expression* exp1;
        Expression* exp2;

    public:
        LayoutManager(FunctionFactory* functionFactory, LayoutChanger* layoutChanger, ScreenFactory* screenFactory, Expression* exp1, Expression* exp2);
        ~LayoutManager();

        void init();

        void OnPress(char row, char col);

        void OnRelease(char row, char col);

        void ChangeLayout(char number);

        void IncrementLayout(char num);

        static void ChangeLayoutCb(void * this_ptr, char number);
        static void IncrementLayoutCb(void * this_ptr, char number);

        Layout* CurrentLayout();

    private:
        void setup_functions(LayoutChanger* layoutChanger, FunctionFactory* functionFactory);
        void setup_buttons();
        void setup_layouts();
        void setup_screens();
};

#endif