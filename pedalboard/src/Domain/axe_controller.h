#pragma once

class AxeController {
    public:
        virtual void Init();
        virtual void SendSceneChange(int scene);
        virtual void sendPresetIncrement();
        virtual void sendPresetDecrement();
        virtual void sendSceneIncrement();
        virtual void sendSceneDecrement();
        virtual void sendPresetChange(const unsigned short preset);
        virtual void sendSceneChange(const unsigned short scene);
        virtual void sendTap();
        virtual void toggleTuner();
};