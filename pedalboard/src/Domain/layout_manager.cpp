#include "pch.h"
#include "constants.h"
#include "control.h"
#include "button.h"
#include "layout_definition.h"
#include "layout_manager.h"
#include "layout.h"
#include "function/function.h"
#include "layout_changer.h"
#include "function/all_functions.h"
#include "function/function_factory.h"

LayoutManager::LayoutManager(FunctionFactory* functionFactory) {
    this->functionFactory = functionFactory;

    this->layoutChanger = new LayoutChanger();
}

LayoutManager::~LayoutManager() {
    delete this->layoutChanger;
    
    for (int i = 0; i < LAYOUTS; i++) {
        delete this->layouts[i];
    }
    delete this->layouts;

    for (int row = 0; row < FS_ROWS; row++)
        for (int col = 0; col < FS_COLS; col++)
            delete this->buttons[row][col];
    delete this->buttons;
}

void LayoutManager::init() {  

    layoutChanger->SubscribeToLayoutSelect(LayoutManager::ChangeLayoutCb, this);
    layoutChanger->SubscribeToLayoutIncrement(LayoutManager::IncrementLayoutCb, this);

    this->setup_buttons();
    this->setup_functions(layoutChanger, this->functionFactory);
    this->setup_layouts();
}

void LayoutManager::setup_functions(LayoutChanger* layoutChanger, FunctionFactory* functionFactory) {
    this->numFunctions = 21;
    this->functions = new Function*[this->numFunctions];
    functions[FunctionName::layout_select_1] = functionFactory->LayoutSelect(1);
    functions[FunctionName::layout_select_2] = functionFactory->LayoutSelect(2);
    functions[FunctionName::layout_incr] = functionFactory->LayoutIncrement();
    functions[FunctionName::layout_decr] = functionFactory->LayoutDecrement();
    functions[FunctionName::scene_select_1] = functionFactory->SceneSelect(1);
    functions[FunctionName::scene_select_2] = functionFactory->SceneSelect(2);
    functions[FunctionName::scene_select_3] = functionFactory->SceneSelect(3);
    functions[FunctionName::scene_select_4] = functionFactory->SceneSelect(4);
    functions[FunctionName::scene_select_5] = functionFactory->SceneSelect(5);
    functions[FunctionName::scene_select_6] = functionFactory->SceneSelect(6);
    functions[FunctionName::scene_select_7] = functionFactory->SceneSelect(7);
    functions[FunctionName::scene_select_8] = functionFactory->SceneSelect(8);
    functions[FunctionName::scene_decr] = functionFactory->SceneDecrement(1);
    functions[FunctionName::scene_icnr] = functionFactory->SceneIncrement(1);
    functions[FunctionName::exp_1_toggle] = functionFactory->ExpToggle(1);
    functions[FunctionName::exp_2_toggle] = functionFactory->ExpToggle(2);
    functions[FunctionName::tuner_toggle] = functionFactory->TunerToggle();
    functions[FunctionName::tap_tempo] = functionFactory->TapTempo();
    functions[FunctionName::preset_decr] = functionFactory->PresetDecrement(1);
    functions[FunctionName::preset_incr] = functionFactory->PresetIncrement(1);
    functions[FunctionName::preset_incr_10] = functionFactory->PresetIncrement(10);
}

void LayoutManager::setup_layouts() {
    this->layouts = new Layout*[LAYOUTS];

    for (int layout = 0; layout < LAYOUTS; layout++) {
        Control*** controls = new Control**[FS_ROWS];
        
        for (int row = 0; row < FS_ROWS; row++) {
            controls[row] = new Control*[FS_COLS];

            for (int col = 0; col < FS_COLS; col++) {
                controls[row][col] = new Control(this->buttons[row][col], this->functions[layoutDefinitions[layout][row][col]]);
            }
        }

        this->layouts[layout] = new Layout(controls, FS_ROWS, FS_COLS);
    }

    this->layoutNumber = 0;
    this->activeLayout = this->layouts[0];
}

void LayoutManager::setup_buttons() {
    this->buttons = new Button**[FS_ROWS];
    for (int row = 0; row < FS_ROWS; row++) {
        buttons[row] = new Button*[FS_COLS];
        for (int col = 0; col < FS_COLS; col++)
            buttons[row][col] = new Button();
    }
}

void LayoutManager::OnPress(int row, int col) {    
    this->buttons[row][col]->OnPress();
}

void LayoutManager::OnRelease(int row, int col) {
    this->buttons[row][col]->OnRelease();
}

void LayoutManager::ChangeLayoutCb(void * this_ptr, int number) {
    ((LayoutManager*)this_ptr)->ChangeLayout(number);
}

void LayoutManager::ChangeLayout(int number) {
    this->activeLayout->Exit();
    this->activeLayout = layouts[number];
}

void LayoutManager::IncrementLayoutCb(void * this_ptr, int number) {
    ((LayoutManager*)this_ptr)->IncrementLayout(number);
}

void LayoutManager::IncrementLayout(int num) {
    this->activeLayout->Exit();

    this->layoutNumber += num;
    if (this->layoutNumber >= LAYOUTS) {
        this->layoutNumber -= LAYOUTS;
    }
    if (this->layoutNumber < 0) {
        this->layoutNumber += LAYOUTS;
    }
    this->activeLayout = layouts[this->layoutNumber];
}

Layout* LayoutManager::CurrentLayout() {
    return this->activeLayout;
}