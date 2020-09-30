#include "pch.h"
#include "../../src/Domain/preset.h"

class FakePreset : public Preset {
	unsigned short getPresetNumber() {
		return 1;
	}

	unsigned short getSelectedSceneNumber() {
		return 1;
	}

	void getPresetName(char* presetNameOut, short capacity) {
		presetNameOut[0] = '\0';
	}

	unsigned short getEffectCount() {
		return 0;
	}
	
	void getEffectName(unsigned short index, char* nameOut, unsigned short capacity) {
		nameOut = "";
	}

	bool getEffectBypassed(unsigned short index) {
		return false;
	}
};