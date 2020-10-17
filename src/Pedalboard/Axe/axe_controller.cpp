#define AXE_DEBUG 1
#define AXE_DEBUG_SYSEX 1

#include "../../Domain/axe_controller.h"
#include <AxeFxControl.h>
#include <Arduino.h>
#include "../../Domain/logger.h"
#include "../../Domain/preset.h"
#include "preset_wrapper.h"

#define MIDI_CC_OUTPUT1_VOL 100

#define MIDI_CHANNEL 1

//A list of all of the scenes for this preset
unsigned long sceneRequestTime[NUM_SCENES];
bool scenesArrived[NUM_SCENES];
bool presetArrived = false;

AxeSystem axe;

PresetWrapper* thePreset = nullptr;
PresetChangeCallback outerPresetChangeCallback;
TheTunerDataCallback outerTunerData;

void onPresetChange(AxePreset axePreset) {
	Logger::log("Preset change");
	thePreset->updatePreset(axePreset);
	outerPresetChangeCallback(thePreset);	

	presetArrived = true;
}

void onEffectsChange(const PresetNumber number, AxePreset axePreset) {
	thePreset->updatePreset(axePreset);
	outerPresetChangeCallback(thePreset);
}

void initSceneState() {
	//Reset the scene list for the new preset
	for (byte sceneNumber = 1; sceneNumber <= NUM_SCENES; sceneNumber++) {
		scenesArrived[sceneNumber - 1] = false;
		sceneRequestTime[sceneNumber - 1] = -1;
		thePreset->setScene(sceneNumber, "");
	}
}

void onPresetChanging(const PresetNumber number) {
	Logger::log("Preset changing");
	presetArrived = false;
	initSceneState();
}

char msg[10];

void onPresetName(const PresetNumber presetNumber, const char* name, const byte length) {
	Logger::log("Preset name: ");
	Logger::log(name);
	Logger::log("\n");
}

void onSceneName(const SceneNumber sceneNumber, const char* name, const byte length) {
	Logger::log("Scene name");
	if (scenesArrived[sceneNumber - 1]) // don't process duplicate
		return;

	scenesArrived[sceneNumber - 1] = true;
	thePreset->setScene(sceneNumber, name);

	for (int i = 0; i < NUM_SCENES; i++) {
		if (!scenesArrived[i]) {
			sceneRequestTime[i] = millis();
			axe.requestSceneName(i + 1);
			break;
		}
	}
}

void onTunerData(const char* note, const byte string, const byte fineTune) {
	outerTunerData(note, string, fineTune);
}

void AxeController::Init(void (*tapTempoCallback)(), PresetChangeCallback presetChangeCallback, TheTunerDataCallback tunerData) {
	outerPresetChangeCallback = presetChangeCallback;	
	outerTunerData = tunerData;

	axe.begin(Serial2, MIDI_CHANNEL);

	thePreset = new PresetWrapper();
	initSceneState();
	axe.fetchEffects(true);
	axe.registerPresetNameCallback(onPresetName);
	axe.registerPresetChangingCallback(onPresetChanging);
	axe.registerPresetChangeCallback(onPresetChange);
	axe.registerEffectsReceivedCallback(onEffectsChange);
	axe.registerTapTempoCallback(tapTempoCallback);
	axe.registerSceneNameCallback(onSceneName);
	axe.registerTunerDataCallback(onTunerData);
	axe.requestPresetDetails();
}

void AxeController::Update() {
	axe.update();
}

void AxeController::SendSceneChange(int scene) {
	axe.sendSceneChange(scene);
}

void AxeController::sendPresetIncrement() {
	axe.sendPresetIncrement();
}

void AxeController::sendPresetDecrement() {
	axe.sendPresetDecrement();
}

void AxeController::sendSceneIncrement() {
	axe.sendSceneIncrement();
}

void AxeController::sendSceneDecrement() {
	axe.sendSceneDecrement();
}

void AxeController::sendPresetChange(const unsigned short preset) {
	axe.sendPresetChange(preset);
}

void AxeController::sendSceneChange(const unsigned short scene) {
	axe.sendSceneChange(scene);
}

void AxeController::sendTap() {
	axe.sendTap();
}

void AxeController::toggleTuner() {
	axe.toggleTuner();
}

void AxeController::sendExpressionPedalValue(unsigned short expNum, unsigned short expValue) {
	axe.sendControlChange(expNum == 1 ? 63 : 62, expValue, MIDI_CHANNEL);
}

void AxeController::changeEffectStatus(unsigned short effectIndex, bool enable) {
	thePreset->changeEffectStatus(effectIndex, enable);
}

void AxeController::sendMute(bool mute) {
	axe.sendControlChange(MIDI_CC_OUTPUT1_VOL, mute ? 0 : 127, MIDI_CHANNEL);
}

bool AxeController::tunerEngaged() {
	return axe.isTunerEngaged();
}