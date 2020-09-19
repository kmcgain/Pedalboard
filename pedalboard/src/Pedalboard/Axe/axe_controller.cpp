#include "../../Domain/axe_controller.h"
#include <AxeFxControl.h>
#include <Arduino.h>
#include "../../Domain/logger.h"
#include "../../Domain/preset.h"
#include "preset_wrapper.h"


AxeSystem axe;

PresetWrapper* thePreset = nullptr;
PresetChangeCallback outerPresetChangeCallback;
uint8_t retrievedScene = 0;

void onPresetChange(AxePreset axePreset) {
	Logger::log("Got preset");

	thePreset->updatePreset(axePreset);
	outerPresetChangeCallback(thePreset);	
}

void initSceneState() {
	//Reset the scene list for the new preset
	for (byte sceneNumber = 0; sceneNumber <= NUM_SCENES; sceneNumber++) {
		thePreset->setScene(sceneNumber, "");
	}
	retrievedScene = 0;
}

void onPresetChanging(const PresetNumber number) {
	initSceneState();
}


char msg[30];

void onSceneName(const SceneNumber sceneNumber, const char* name, const byte length) {	
	thePreset->setScene(sceneNumber, name);
	
	if (++retrievedScene == sceneNumber)
		retrievedScene++;
	if (retrievedScene > NUM_SCENES)
		return;
	axe.requestSceneName(retrievedScene);
}

void AxeController::Init(void (*tapTempoCallback)(), PresetChangeCallback presetChangeCallback) {
	outerPresetChangeCallback = presetChangeCallback;	

	axe.begin(Serial2);

	thePreset = new PresetWrapper();
	initSceneState();

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