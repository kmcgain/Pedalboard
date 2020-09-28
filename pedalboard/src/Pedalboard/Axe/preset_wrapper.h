#pragma once

#include <AxeFxControl.h>
#include "../../Domain/preset.h"
#include "../../Domain/str_fn.h"

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

	void getPresetName(char* presetNameOut, short capacity) {
		strTerm(presetNameOut, this->preset.getPresetName(), capacity);
	}
};