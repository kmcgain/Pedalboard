#ifndef LAYOUT_CHANGER_H
#define LAYOUT_CHANGER_H

class LayoutChanger {
    private:
        void (*layoutSelectCallbacks)(void*, int);
        void (*layoutIncrementCallbacks)(void*, int);
        void* layoutSelectCbThis;
        void* layoutIncrementCbThis;

    public:
        void SubscribeToLayoutSelect(void (*callback)(void*, int), void* layoutSelectCbThis);

        void SubscribeToLayoutIncrement(void (*callback)(void*, int), void* layoutIncrementCbThis);

        void SelectLayout(int layout);
        
        void IncrementLayout(int num);
};

#endif