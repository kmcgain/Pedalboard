#ifndef LAYOUT_MANAGER_H
#define LAYOUT_MANAGER_H

#include "layout.h"
#include "function.h"
#include "button.h"
#include "layout_changer.h"

class LayoutManager {
    private: 
        Layout** layouts;
        Layout* activeLayout;
        Button*** buttons;
        Function** functions;
        int layoutNumber;

    public:
        LayoutManager();

        void init();

        void OnPress(int row, int col);

        void OnRelease(int row, int col);

        void ChangeLayout(int number);

        void IncrementLayout(int num);

        static void ChangeLayoutCb(void * this_ptr, int number);
        static void IncrementLayoutCb(void * this_ptr, int number);

    private:
        void setup_functions(LayoutChanger* layoutChanger);
        void setup_buttons();
        void setup_layouts();
};

#endif