#pragma once
#include "preset.h"

typedef void (*PresetChangeCallback)(Preset*);
typedef void (*TheTunerDataCallback)(const char *, const short, const short); // note, string (1-6), fineTune
typedef char PresetNames[512][MAX_PRESET_NAME_LENGTH];

class AxeController {

public:
    virtual void Init(void (*tapTempoCallback)(), PresetChangeCallback presetChangeCallback, TheTunerDataCallback tunerDataCallback);
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
    virtual bool tunerEngaged();
    virtual PresetNames* presetNames();
    virtual int currentPresetNumber();
};