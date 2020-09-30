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
PresetNumber loadingNumber = -1;
unsigned long timePresetChangeStarted = -1;
unsigned long forceLoadTime = -1;
bool allFetched = false;

void onPresetChange(AxePreset axePreset) {
	Logger::log("\nPREEST CHANGE\n");
	thePreset->updatePreset(axePreset);
	outerPresetChangeCallback(thePreset);	
}

void onEffectsChange(const PresetNumber number, AxePreset axePreset) {
	Logger::log("\nEFFECTS REC\n");
	thePreset->updatePreset(axePreset);
	outerPresetChangeCallback(thePreset);
}

void initSceneState() {
	Logger::log("\nResetting scenes\n");
	//Reset the scene list for the new preset
	for (byte sceneNumber = 1; sceneNumber <= NUM_SCENES; sceneNumber++) {
		scenes[sceneNumber - 1] = false;
		thePreset->setScene(sceneNumber, "");
	}

	allFetched = false;
	timePresetChangeStarted = millis();
	//retrievedScene = 0;
}

void onPresetChanging(const PresetNumber number) {
	if (loadingNumber == number) return;
	loadingNumber = number;
	initSceneState();
}

char msg[10];

void onPresetName(const PresetNumber presetNumber, const char* name, const byte length) {

}

void fetchNextScene() {
	int i;
	for (i = 0; i < NUM_SCENES; i++) {
		if (!scenes[i]) {
			Logger::log("\nRequesting: ");
			Logger::log(i + 1);

			axe.requestSceneName(i + 1);
			break;
		}
	}
	allFetched = i == NUM_SCENES;
}

void onSceneName(const SceneNumber sceneNumber, const char* name, const byte length) {	
	if (scenes[sceneNumber - 1]) // don't process duplicate
		return;

	Logger::log("\nOn scene: ");
	Logger::log(sceneNumber);
	Logger::log(" : ");
	Logger::log(name);

	thePreset->setScene(sceneNumber, name);
	scenes[sceneNumber - 1] = true;

	//sprintf(msg, "Retr: %d\n", retrievedScene);
	//Logger::log(msg);

	//sprintf(msg, "%d\n", sceneNumber);
	//Logger::log(msg);

	// TODO: Investigate issue where we get duplicate calls to this

	fetchNextScene();

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
	axe.registerEffectsReceivedCallback(onEffectsChange);
	axe.registerTapTempoCallback(tapTempoCallback);
	axe.registerSceneNameCallback(onSceneName);
	axe.requestPresetDetails();
}

void AxeController::Update() {
	// Deal with lost scene names - found that sometimes it doesn't communicate correctly
	if (timePresetChangeStarted != -1 && millis() - timePresetChangeStarted > 2000 && !allFetched && (forceLoadTime == -1 || millis() - forceLoadTime > 2000)) {
		forceLoadTime = millis();
		fetchNextScene();
	}

	axe.update();
}

void AxeController::SendSceneChange(int scene) {
	axe.sendSceneChange(scene);
}


void AxeController::sendPresetIncrement() {
	Logger::log("\nSEND PREEST I\n");
	axe.sendPresetIncrement();
}

void AxeController::sendPresetDecrement() {
	Logger::log("\nSEND PREEST D\n");
	axe.sendPresetDecrement();
}

void AxeController::sendSceneIncrement() {
	axe.sendSceneIncrement();
}

void AxeController::sendSceneDecrement() {
	axe.sendSceneDecrement();
}

void AxeController::sendPresetChange(const unsigned short preset) {
	Logger::log("\nSEND PREEST CHANGE: ");
	Logger::log(preset);
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

void AxeController::changeEffectStatus(unsigned short effectIndex, bool enable) {
	thePreset->changeEffectStatus(effectIndex, enable);
}
