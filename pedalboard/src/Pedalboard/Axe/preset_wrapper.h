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

	unsigned short getEffectCount() {
		return preset.getEffectCount();
	}

	void getEffectName(unsigned short index, char* nameOut, unsigned short capacity) {
		preset.getEffectAt(index).copyEffectTag(nameOut, capacity);
	}

	bool getEffectBypassed(unsigned short index) {
		return preset.getEffectAt(index).isBypassed();
	}

	void changeEffectStatus(unsigned short effectIndex, bool enable) {
		if (preset.getEffectCount() <= effectIndex || effectIndex < 0)
			return; // out of bounds

		// We first get effect by index but then go via id because it gives us a pointer to original meaning the state is synced correctly
		AxeEffect effect = preset.getEffectAt(effectIndex);
		AxeEffect *theEffect = preset.getEffectById(effect.getEffectId());

		// NOTES: Currently the issue is we get a copy of effect so modifying it doesn't update state, we need to modify the actual state of the preset;
		
		if (enable)
			theEffect->enable();
		else
			theEffect->bypass();
	}
};