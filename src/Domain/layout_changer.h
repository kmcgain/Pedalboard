#ifndef LAYOUT_CHANGER_H
#define LAYOUT_CHANGER_H

class LayoutChanger {
    private:
        void (*layoutSelectCallbacks)(void*, byte);
        void (*layoutIncrementCallbacks)(void*, byte);
        void* layoutSelectCbThis;
        void* layoutIncrementCbThis;

        int selectedLayout = 1;
        bool presetSelect = false;
    public:
        void SubscribeToLayoutSelect(void (*callback)(void*, byte), void* layoutSelectCbThis);

        void SubscribeToLayoutIncrement(void (*callback)(void*, byte), void* layoutIncrementCbThis);

        void SelectLayout(byte layout);
        
        void IncrementLayout(byte num);

        void PresetSelect();
};

#endif