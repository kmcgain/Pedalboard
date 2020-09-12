#ifndef LAYOUT_CHANGER_H
#define LAYOUT_CHANGER_H

class LayoutChanger {
    private:
        void (*layoutSelectCallbacks)(void*, char);
        void (*layoutIncrementCallbacks)(void*, char);
        void* layoutSelectCbThis;
        void* layoutIncrementCbThis;

    public:
        void SubscribeToLayoutSelect(void (*callback)(void*, char), void* layoutSelectCbThis);

        void SubscribeToLayoutIncrement(void (*callback)(void*, char), void* layoutIncrementCbThis);

        void SelectLayout(char layout);
        
        void IncrementLayout(char num);
};

#endif