#ifndef LAYOUT_CHANGER_H
#define LAYOUT_CHANGER_H

class LayoutChanger {
    private:
        void (*layoutSelectCallbacks)(void*, int);
        void (*layoutIncrementCallbacks)(void*, int);
        void* layoutSelectCbThis;
        void* layoutIncrementCbThis;

    public:
        void SubscribeToLayoutSelect(void (*callback)(void*, int), void* layoutSelectCbThis) {
            this->layoutSelectCallbacks = callback;
            this->layoutSelectCbThis = layoutSelectCbThis;
        }

        void SubscribeToLayoutIncrement(void (*callback)(void*, int), void* layoutIncrementCbThis) {
            this->layoutIncrementCallbacks = callback;
            this->layoutIncrementCbThis = layoutSelectCbThis;
        }

        void SelectLayout(int layout) {
            this->layoutSelectCallbacks(this->layoutSelectCbThis, layout);
        }
        
        void IncrementLayout(int num) {
            this->layoutIncrementCallbacks(this->layoutIncrementCbThis, num);
        }
};

#endif