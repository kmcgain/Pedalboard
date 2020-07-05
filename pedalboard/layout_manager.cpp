#include "constants.h"
// #include "control.h"
#include "button.h"
// #include "layout_definition.h"
#include "layout_manager.h"

void LayoutManager::init() {        
    this->setup_buttons();
    this->setup_functions();
    this->setup_layouts();
}


void LayoutManager::setup_functions() {
    // this->functions[FunctionName::layout_select_1] = new Function();
    // this->functions[FunctionName::layout_select_2] = new Function();
    // this->functions[FunctionName::layout_incr] = new Function();
    // this->functions[FunctionName::layout_decr] = new Function();
    // this->functions[FunctionName::scene_select_1] = new Function();
    // this->functions[FunctionName::scene_select_2] = new Function();
    // this->functions[FunctionName::scene_select_3] = new Function();
    // this->functions[FunctionName::scene_select_4] = new Function();
    // this->functions[FunctionName::scene_select_5] = new Function();
    // this->functions[FunctionName::scene_select_6] = new Function();
    // this->functions[FunctionName::scene_select_7] = new Function();
    // this->functions[FunctionName::scene_select_8] = new Function();
    // this->functions[FunctionName::scene_decr] = new Function();
    // this->functions[FunctionName::scene_icnr] = new Function();
    // this->functions[FunctionName::exp_1_toggle] = new Function();
    // this->functions[FunctionName::exp_2_toggle] = new Function();
    // this->functions[FunctionName::tuner_toggle] = new Function();
    // this->functions[FunctionName::tap_tempo] = new Function();
    // this->functions[FunctionName::preset_decr] = new Function();
    // this->functions[FunctionName::preset_incr] = new Function();
    // this->functions[FunctionName::preset_incr_10] = new Function();
}


void LayoutManager::setup_layouts() {
    for (int layout = 0; layout < LAYOUTS; layout++) {
        
    }
}

void LayoutManager::setup_buttons() {
    this->buttons = new Button**[FS_ROWS];
    for (int row; row < FS_ROWS; row++) {
        buttons[row] = new Button*[FS_COLS];
        for (int col; col < FS_COLS; col++)
            buttons[row][col] = new Button();
    }
}

void LayoutManager::OnPress(int row, int col) {
    this->buttons[row][col]->OnPress();
}

void LayoutManager::OnRelease(int row, int col) {
    this->buttons[row][col]->OnRelease();
}