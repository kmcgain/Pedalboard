#ifndef LAYOUT_MANAGER_H
#define LAYOUT_MANAGER_H

#include "layout.h"

class Function {    
};

class LayoutManager {
    private: 
        Layout* activeLayout;
        Button*** buttons;
        Function* functions[20];

    public:
        void init();

        void OnPress(int row, int col);

        void OnRelease(int row, int col);

    private:
        void setup_functions();
        void setup_buttons();
        void setup_layouts();
};

#endif