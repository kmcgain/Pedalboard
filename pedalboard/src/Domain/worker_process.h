#pragma once
#include "axe_controller.h"
#include "preset.h"

class WorkerProcess {
private:
	AxeController* axeController;

public:
	WorkerProcess(AxeController* axeController);
	void OneStep(Preset* currentPreset);
	void PrintDebug();
};