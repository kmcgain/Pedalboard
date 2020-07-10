#include "layout_changer.h"

void LayoutChanger::SubscribeToLayoutSelect(void (*callback)(void*, int), void* layoutSelectCbThis) {
    this->layoutSelectCallbacks = callback;
    this->layoutSelectCbThis = layoutSelectCbThis;
}

void LayoutChanger::SubscribeToLayoutIncrement(void (*callback)(void*, int), void* layoutIncrementCbThis) {
    this->layoutIncrementCallbacks = callback;
    this->layoutIncrementCbThis = layoutSelectCbThis;
}

void LayoutChanger::SelectLayout(int layout) {
    this->layoutSelectCallbacks(this->layoutSelectCbThis, layout);
}

void LayoutChanger::IncrementLayout(int num) {
    this->layoutIncrementCallbacks(this->layoutIncrementCbThis, num);
}