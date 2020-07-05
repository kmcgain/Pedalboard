#include "constants.h"
#include "control.h"
#include "button.h"
#include "layout_definition.h"
#include "layout_manager.h"
#include "layout.h"
#include "function.h"
#include "function_impl.h"
#include "layout_changer.h"

LayoutManager::LayoutManager() {
}

void LayoutManager::init() {    
    LayoutChanger* layoutChanger = new LayoutChanger();
    layoutChanger->SubscribeToLayoutSelect(LayoutManager::ChangeLayoutCb, this);
    layoutChanger->SubscribeToLayoutIncrement(LayoutManager::IncrementLayoutCb, this);

    this->setup_buttons();
    this->setup_functions(layoutChanger);
    this->setup_layouts();
}

void LayoutManager::setup_functions(LayoutChanger* layoutChanger) {
    Function** functions = new Function*[20];
    functions[FunctionName::layout_select_1] = new LayoutSelectFunction(1, layoutChanger);
    functions[FunctionName::layout_select_2] = new LayoutSelectFunction(2, layoutChanger);
    functions[FunctionName::layout_incr] = new LayoutIncrementFunction(layoutChanger);
    functions[FunctionName::layout_decr] = new LayoutDecrementFunction(layoutChanger);
    functions[FunctionName::scene_select_1] = new SceneSelectFunction(1);
    functions[FunctionName::scene_select_2] = new SceneSelectFunction(2);
    functions[FunctionName::scene_select_3] = new SceneSelectFunction(3);
    functions[FunctionName::scene_select_4] = new SceneSelectFunction(4);
    functions[FunctionName::scene_select_5] = new SceneSelectFunction(5);
    functions[FunctionName::scene_select_6] = new SceneSelectFunction(6);
    functions[FunctionName::scene_select_7] = new SceneSelectFunction(7);
    functions[FunctionName::scene_select_8] = new SceneSelectFunction(8);
    functions[FunctionName::scene_decr] = new SceneDecrementFunction(1);
    functions[FunctionName::scene_icnr] = new SceneIncrementFunction(1);
    functions[FunctionName::exp_1_toggle] = new ExpToggleFunction(1);
    functions[FunctionName::exp_2_toggle] = new ExpToggleFunction(2);
    functions[FunctionName::tuner_toggle] = new TunerToggleFunction();
    functions[FunctionName::tap_tempo] = new TapTempoFunction();
    functions[FunctionName::preset_decr] = new PresetDecrementFunction(1);
    functions[FunctionName::preset_incr] = new PresetIncrementFunction(1);
    functions[FunctionName::preset_incr_10] = new PresetIncrementFunction(10);
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

static void LayoutManager::ChangeLayoutCb(void * this_ptr, int number) {
    ((LayoutManager*)this_ptr)->ChangeLayout(number);
}

void LayoutManager::ChangeLayout(int number) {
    this->activeLayout->Exit();
    this->activeLayout = layouts[number];
}

static void LayoutManager::IncrementLayoutCb(void * this_ptr, int number) {
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