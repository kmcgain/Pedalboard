#include "pch.h"
#include "constants.h"
#include "control.h"
#include "button.h"
#include "screen.h"
#include "layout_definition.h"
#include "layout_manager.h"
#include "layout.h"
#include "function/function.h"
#include "layout_changer.h"
#include "function/all_functions.h"
#include "function/function_factory.h"
#include "screen_factory.h"

LayoutManager::LayoutManager(FunctionFactory* functionFactory, LayoutChanger* layoutChanger, ScreenFactory* screenFactory, Expression* exp1, Expression* exp2) {
    this->functionFactory = functionFactory;
    this->screenFactory = screenFactory;

    this->layoutChanger = layoutChanger;
    this->exp1 = exp1;
    this->exp2 = exp2;
}

LayoutManager::~LayoutManager() {
    delete this->layoutChanger;
    
    if (this->layouts != nullptr) {
        for (byte i = 0; i < LAYOUTS; i++) {
            if (this->layouts[i] != nullptr)
                delete this->layouts[i];
        }
        delete this->layouts;
    }

    if (this->buttons != nullptr) {
        for (byte row = 0; row < FS_ROWS; row++)
            for (byte col = 0; col < FS_COLS; col++)
                if (this->buttons[row][col] != nullptr)
                    delete this->buttons[row][col];
        delete this->buttons;
    }
}

void LayoutManager::init() {  
    this->layoutChanger->SubscribeToLayoutSelect(&LayoutManager::ChangeLayoutCb, this);
    this->layoutChanger->SubscribeToLayoutIncrement(&LayoutManager::IncrementLayoutCb, this);
    
    this->setup_buttons();
    this->setup_screens();
    this->setup_functions(this->layoutChanger, this->functionFactory);
    this->setup_layouts();
}

void LayoutManager::setup_functions(LayoutChanger* layoutChanger, FunctionFactory* functionFactory) {
    //this->functions = new Function*[this->numFunctions];

    
    this->functions[FunctionName::layout_select_1] = functionFactory->LayoutSelect(1);
    this->functions[FunctionName::layout_select_2] = functionFactory->LayoutSelect(2);
    this->functions[FunctionName::layout_incr] = functionFactory->LayoutIncrement();
    this->functions[FunctionName::layout_decr] = functionFactory->LayoutDecrement();
    this->functions[FunctionName::scene_select_1] = functionFactory->SceneSelect(1);
    this->functions[FunctionName::scene_select_2] = functionFactory->SceneSelect(2);
    this->functions[FunctionName::scene_select_3] = functionFactory->SceneSelect(3);
    this->functions[FunctionName::scene_select_4] = functionFactory->SceneSelect(4);
    this->functions[FunctionName::scene_select_5] = functionFactory->SceneSelect(5);
    this->functions[FunctionName::scene_select_6] = functionFactory->SceneSelect(6);
    this->functions[FunctionName::scene_select_7] = functionFactory->SceneSelect(7);
    this->functions[FunctionName::scene_select_8] = functionFactory->SceneSelect(8);
    this->functions[FunctionName::scene_decr] = functionFactory->SceneDecrement(1);
    this->functions[FunctionName::scene_icnr] = functionFactory->SceneIncrement(1);
    short exp1Options[3] = {1,2,3};
    short exp2Options[3] = {4,5,6};
    this->functions[FunctionName::exp_1_toggle] = functionFactory->ExpToggle(1, exp1Options, 3, this->exp1);
    this->functions[FunctionName::exp_2_toggle] = functionFactory->ExpToggle(2, exp2Options, 3, this->exp2);
    this->functions[FunctionName::tuner_toggle] = functionFactory->TunerToggle();
    this->functions[FunctionName::tap_tempo] = functionFactory->TapTempo();
    this->functions[FunctionName::preset_decr] = functionFactory->PresetDecrement(1);
    this->functions[FunctionName::preset_incr] = functionFactory->PresetIncrement(1);
    this->functions[FunctionName::preset_incr_10] = functionFactory->PresetIncrement(10);
    this->functions[FunctionName::preset_display] = functionFactory->PresetDisplay();
    
    this->functions[FunctionName::effect1] = functionFactory->Effect(1);
    this->functions[FunctionName::effect2] = functionFactory->Effect(2);
    this->functions[FunctionName::effect3] = functionFactory->Effect(3);
    this->functions[FunctionName::effect4] = functionFactory->Effect(4);
    this->functions[FunctionName::effect5] = functionFactory->Effect(5);
    this->functions[FunctionName::effect6] = functionFactory->Effect(6);
    this->functions[FunctionName::effect7] = functionFactory->Effect(7);
    this->functions[FunctionName::effect8] = functionFactory->Effect(8);
    this->functions[FunctionName::effect9] = functionFactory->Effect(9);
    this->functions[FunctionName::effect10] = functionFactory->Effect(10);
    this->functions[FunctionName::mute] = functionFactory->Mute();
}

void LayoutManager::setup_preset_select_layout() {
    // Setup preset select layout - a special hidden layout
    // This layout just has the same function on all buttons. We'll handle 
    // the logic of which button does what within function implementation
    PresetSelector* presetSelector = new PresetSelector();
    Control*** controls = new Control**[FS_ROWS];
        
    for (byte row = 0; row < FS_ROWS; row++) {
        controls[row] = new Control*[FS_COLS];
        
        for (byte col = 0; col < FS_COLS; col++) {
            auto functionIndex = FunctionName::preset_select;
            auto function = functionFactory->PresetFullSelect(col + (row * FS_COLS), presetSelector);
            controls[row][col] = new Control(this->buttons[row][col], function, this->screens[row][col], col + (row * FS_COLS));                
        }
    }

    this->layouts[LAYOUTS] = new Layout(controls, FS_ROWS, FS_COLS);
}

void LayoutManager::setup_layouts() {
    this->layouts = new Layout*[LAYOUTS+1];

    for (byte layout = 0; layout < LAYOUTS; layout++) {
        Control*** controls = new Control**[FS_ROWS];
        
        for (byte row = 0; row < FS_ROWS; row++) {
            controls[row] = new Control*[FS_COLS];
            
            for (byte col = 0; col < FS_COLS; col++) {
                auto functionIndex = layoutDefinitions[layout][FS_ROWS - 1 - row][col];
                if (functionIndex >= sizeof(this->functions) / sizeof(this->functions[0])) {
#ifdef TEST
                    throw std::runtime_error("Bad function defintion");
#endif
                    Logger::log("Bad function defintion, will assign unexpected function");
                    functionIndex = FunctionName::layout_select_1;
                }
                
                controls[row][col] = new Control(this->buttons[row][col], this->functions[functionIndex], this->screens[row][col], col + (row * FS_COLS));                
            }
        }

        this->layouts[layout] = new Layout(controls, FS_ROWS, FS_COLS);
    }

    setup_preset_select_layout();


    this->layoutNumber = 0;
    this->activeLayout = this->layouts[0];
}

void LayoutManager::setup_buttons() {
    this->buttons = new Button**[FS_ROWS];
    
    for (byte row = 0; row < FS_ROWS; row++) {
        this->buttons[row] = new Button*[FS_COLS];
                
        for (byte col = 0; col < FS_COLS; col++) {
            this->buttons[row][col] = new Button();
        }
    }
}


void LayoutManager::setup_screens() {
    this->screens = new Screen * *[FS_ROWS];

    byte screenNumber = 0;
    for (byte row = 0; row < FS_ROWS; row++) {
        this->screens[row] = new Screen * [FS_COLS];

        for (byte col = 0; col < FS_COLS; col++) {
            this->screens[row][col] = this->screenFactory->CreateScreen(screenNumber++);            
        }
    }
}

void LayoutManager::OnPress(byte row, byte col) {
    this->buttons[row][col]->OnPress();
}

void LayoutManager::OnRelease(byte row, byte col) {
    this->buttons[row][col]->OnRelease();
}

void LayoutManager::ChangeLayoutCb(void * this_ptr, byte number) {
    ((LayoutManager*)this_ptr)->ChangeLayout(number);
}

void LayoutManager::ChangeLayout(byte layoutNumber) {
    if (layoutNumber > LAYOUTS || layoutNumber < 0)
        return;
    // Layout 0 is special - it refers to preset selector
    Logger::log("Changing to layout: ");
    Logger::log((int)layoutNumber);

    this->activeLayout->Exit();
    this->activeLayout = layouts[layoutNumber == 0 ? LAYOUTS : layoutNumber-1];
    this->activeLayout->Invalidate();
}

void LayoutManager::IncrementLayoutCb(void * this_ptr, byte number) {
    ((LayoutManager*)this_ptr)->IncrementLayout(number);
}

void LayoutManager::IncrementLayout(byte num) {
    this->activeLayout->Exit();

    this->layoutNumber += num;
    if (this->layoutNumber >= LAYOUTS) {
        this->layoutNumber -= LAYOUTS;
    }
    if (this->layoutNumber < 0) {
        this->layoutNumber += LAYOUTS;
    }
    this->activeLayout = layouts[this->layoutNumber];
    this->activeLayout->Invalidate();
}

Layout* LayoutManager::CurrentLayout() {
    return this->activeLayout;
}