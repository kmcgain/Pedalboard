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
        byte numLayouts;
        Layout** layouts;
        Layout* activeLayout;
        Button*** buttons;
        Screen*** screens;
        Function* functions[33];
        byte layoutNumber;
        LayoutChanger* layoutChanger;
        FunctionFactory* functionFactory;
        ScreenFactory* screenFactory;
        Expression* exp1;
        Expression* exp2;

    public:
        LayoutManager(FunctionFactory* functionFactory, LayoutChanger* layoutChanger, ScreenFactory* screenFactory, Expression* exp1, Expression* exp2);
        ~LayoutManager();

        void init();

        void OnPress(byte row, byte col);

        void OnRelease(byte row, byte col);

        void ChangeLayout(byte number);

        void IncrementLayout(byte num);

        static void ChangeLayoutCb(void * this_ptr, byte number);
        static void IncrementLayoutCb(void * this_ptr, byte number);

        Layout* CurrentLayout();

    private:
        void setup_functions(LayoutChanger* layoutChanger, FunctionFactory* functionFactory);
        void setup_buttons();
        void setup_layouts();
        void setup_screens();
        void setup_preset_select_layout();
};

#endif