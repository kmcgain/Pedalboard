#ifndef LAYOUT_MANAGER_H
#define LAYOUT_MANAGER_H

#include "layout.h"
#include "function/function.h"
#include "button.h"
#include "layout_changer.h"
#include "function/function_factory.h"

class LayoutManager {
    private: 
        Layout** layouts;
        Layout* activeLayout;
        Button*** buttons;
        int numFunctions;
        Function** functions;
        int layoutNumber;
        LayoutChanger* layoutChanger;
        FunctionFactory* functionFactory;

    public:
        LayoutManager(FunctionFactory* functionFactory);
        ~LayoutManager();

        void init();

        void OnPress(int row, int col);

        void OnRelease(int row, int col);

        void ChangeLayout(int number);

        void IncrementLayout(int num);

        static void ChangeLayoutCb(void * this_ptr, int number);
        static void IncrementLayoutCb(void * this_ptr, int number);

        Layout* CurrentLayout();

    private:
        void setup_functions(LayoutChanger* layoutChanger, FunctionFactory* functionFactory);
        void setup_buttons();
        void setup_layouts();
};

#endif