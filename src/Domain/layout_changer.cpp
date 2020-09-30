#include "pch.h"
#include "layout_changer.h"

void LayoutChanger::SubscribeToLayoutSelect(void (*callback)(void*, char), void* layoutSelectCbThis) {
    this->layoutSelectCallbacks = callback;
    this->layoutSelectCbThis = layoutSelectCbThis;
}

void LayoutChanger::SubscribeToLayoutIncrement(void (*callback)(void*, char), void* layoutIncrementCbThis) {
    this->layoutIncrementCallbacks = callback;
    this->layoutIncrementCbThis = layoutSelectCbThis;
}

void LayoutChanger::SelectLayout(char layout) {
    this->layoutSelectCallbacks(this->layoutSelectCbThis, layout);
}

void LayoutChanger::IncrementLayout(char num) {
    this->layoutIncrementCallbacks(this->layoutIncrementCbThis, num);
}