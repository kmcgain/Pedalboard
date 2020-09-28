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
};