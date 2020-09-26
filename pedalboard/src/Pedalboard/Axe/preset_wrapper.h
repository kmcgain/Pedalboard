#pragma once

#include <AxeFxControl.h>
#include "../../Domain/preset.h"

class PresetWrapper : public Preset {
private:
	AxePreset preset;

public:
	void updatePreset(AxePreset& preset) {
		this-> preset = preset;
		this->sequenceNumber++;
	}

	unsigned short getPresetNumber() {
		return this->preset.getPresetNumber();
	}

	unsigned short getSelectedSceneNumber() {
		return this->preset.getSceneNumber();
	}

	const char* getPresetName() {
		return this->preset.getPresetName();
	}
};