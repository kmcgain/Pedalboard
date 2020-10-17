#pragma once
#include "axe_controller.h"
#include "preset.h"
#include "expression.h"
#include "tuner.h"

class WorkerProcess {
private:
	AxeController* axeController;
	Expression* exp1;
	Expression* exp2;

public:
	WorkerProcess(AxeController* axeController);
	void OneStep(Preset* currentPreset, TunerData& tuner);
	void PrintDebug();
};