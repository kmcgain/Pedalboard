#include "../../Domain/axe_controller.h"
#include <AxeFxControl.h>
#include <Arduino.h>
#include "../../Domain/logger.h"
#include "../../Domain/preset.h"
#include "preset_wrapper.h"

//A list of all of the scenes for this preset
bool scenes[NUM_SCENES];

AxeSystem axe;

PresetWrapper* thePreset = nullptr;
PresetChangeCallback outerPresetChangeCallback;

void onPresetChange(AxePreset axePreset) {
	thePreset->updatePreset(axePreset);
	outerPresetChangeCallback(thePreset);	
}

void initSceneState() {
	//Reset the scene list for the new preset
	for (byte sceneNumber = 1; sceneNumber <= NUM_SCENES; sceneNumber++) {
		scenes[sceneNumber - 1] = false;
		thePreset->setScene(sceneNumber, "");
	}
	//retrievedScene = 0;
}

void onPresetChanging(const PresetNumber number) {
	initSceneState();
}

char msg[10];

void onPresetName(const PresetNumber presetNumber, const char* name, const byte length) {

}

void onSceneName(const SceneNumber sceneNumber, const char* name, const byte length) {	
	thePreset->setScene(sceneNumber, name);
	scenes[sceneNumber - 1] = true;

	//sprintf(msg, "Retr: %d\n", retrievedScene);
	//Logger::log(msg);

	//sprintf(msg, "%d\n", sceneNumber);
	//Logger::log(msg);

	// TODO: Investigate issue where we get duplicate calls to this

	for (int i = 0; i < NUM_SCENES; i++) {
		if (!scenes[i]) {
			axe.requestSceneName(i + 1);
			break;
		}
	}

	/*if (++retrievedScene == sceneNumber)
		retrievedScene++;
	if (retrievedScene > NUM_SCENES)
		return;
	axe.requestSceneName(retrievedScene);*/
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
	axe.registerTapTempoCallback(tapTempoCallback);
	axe.registerSceneNameCallback(onSceneName);
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
	/*sprintf(msg, "%d: %d\n", expNum, expValue);
	Logger::log(msg);*/

	axe.sendControlChange(expNum == 1 ? 63 : 62, expValue, AxeSystem::DEFAULT_MIDI_CHANNEL);
}