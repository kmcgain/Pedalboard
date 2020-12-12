#include "pch.h"
#include "layout_changer.h"

void LayoutChanger::SubscribeToLayoutSelect(void (*callback)(void*, byte), void* layoutSelectCbThis) {
    this->layoutSelectCallbacks = callback;
    this->layoutSelectCbThis = layoutSelectCbThis;
}

void LayoutChanger::SubscribeToLayoutIncrement(void (*callback)(void*, byte), void* layoutIncrementCbThis) {
    this->layoutIncrementCallbacks = callback;
    this->layoutIncrementCbThis = layoutSelectCbThis;
}

void LayoutChanger::SelectLayout(byte layout) {
    this->layoutSelectCallbacks(this->layoutSelectCbThis, layout);
    selectedLayout = layout;
}

void LayoutChanger::IncrementLayout(byte num) {
    this->layoutIncrementCallbacks(this->layoutIncrementCbThis, num);
    selectedLayout += num;
}

#define preset_select_layout_number 0
void LayoutChanger::PresetSelect() {
    if (presetSelect) {
        presetSelect = false;    
        this->layoutSelectCallbacks(this->layoutSelectCbThis, selectedLayout);
        return;
    }

    presetSelect = true;
    this->layoutSelectCallbacks(this->layoutSelectCbThis, preset_select_layout_number);
}