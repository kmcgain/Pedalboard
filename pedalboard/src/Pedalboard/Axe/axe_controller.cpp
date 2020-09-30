#include "../../Domain/axe_controller.h"
#include <AxeFxControl.h>
#include <Arduino.h>
#include "../../Domain/logger.h"
#include "../../Domain/preset.h"
#include "preset_wrapper.h"

//A list of all of the scenes for this preset
unsigned long sceneRequestTime[NUM_SCENES];
bool scenesArrived[NUM_SCENES];

AxeSystem axe;

PresetWrapper* thePreset = nullptr;
PresetChangeCallback outerPresetChangeCallback;

void onPresetChange(AxePreset axePreset) {
	thePreset->updatePreset(axePreset);
	outerPresetChangeCallback(thePreset);	
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
	initSceneState();
}

char msg[10];

void onPresetName(const PresetNumber presetNumber, const char* name, const byte length) {

}

void onSceneName(const SceneNumber sceneNumber, const char* name, const byte length) {	
	if (scenesArrived[sceneNumber - 1]) // don't process duplicate
		return;

	thePreset->setScene(sceneNumber, name);
	scenesArrived[sceneNumber - 1] = true;
}

void AxeController::Init(void (*tapTempoCallback)(), PresetChangeCallback presetChangeCallback) {
	outerPresetChangeCallback = presetChangeCallback;	

	axe.begin(Serial2);

	thePreset = new PresetWrapper();
	initSceneState();
	axe.fetchEffects(true);
	axe.registerPresetNameCallback(onPresetName);
	axe.registerPresetChangingCallback(onPresetChanging);
	axe.registerPresetChangeCallback(onPresetChange);
	axe.registerEffectsReceivedCallback(onEffectsChange);
	axe.registerTapTempoCallback(tapTempoCallback);
	axe.registerSceneNameCallback(onSceneName);
	axe.requestPresetDetails();
}

void AxeController::Update() {
	for (int i = 0; i < NUM_SCENES; i++) {
		if (!scenesArrived[i] && (sceneRequestTime[i] == -1 || millis() - sceneRequestTime[i] > 100)) {
			sceneRequestTime[i] = millis();
			axe.requestSceneName(i + 1);
		}
	}

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
	axe.sendControlChange(expNum == 1 ? 63 : 62, expValue, AxeSystem::DEFAULT_MIDI_CHANNEL);
}

void AxeController::changeEffectStatus(unsigned short effectIndex, bool enable) {
	thePreset->changeEffectStatus(effectIndex, enable);
}
