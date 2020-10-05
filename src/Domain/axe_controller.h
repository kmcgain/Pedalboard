#pragma once
#include "preset.h"

typedef void (*PresetChangeCallback)(Preset*);

class AxeController {

public:
    virtual void Init(void (*tapTempoCallback)(), PresetChangeCallback presetChangeCallback);
    virtual void Update();
    virtual void SendSceneChange(int scene);
    virtual void sendPresetIncrement();
    virtual void sendPresetDecrement();
    virtual void sendSceneIncrement();
    virtual void sendSceneDecrement();
    virtual void sendPresetChange(const unsigned short preset);
    virtual void sendSceneChange(const unsigned short scene);
    virtual void sendTap();
    virtual void toggleTuner();
    virtual void sendExpressionPedalValue(unsigned short expNumber, unsigned short pedalValue);
    virtual void changeEffectStatus(unsigned short effectIndex, bool enable);
    virtual void sendMute(bool mute);
};