#include "pch.h"
#include "worker_process.h"
#include "layout_setup.h"
#include "preset.h"


WorkerProcess::WorkerProcess(AxeController* axeController) {
	this->axeController = axeController;
	this->exp1 = new Expression(1, axeController);
	this->exp2 = new Expression(2, axeController);
}

void WorkerProcess::OneStep(Preset* currentPreset, TunerData& tuner) {
	// Handle button presses
	auto lm = GetLayoutManager();
	if (lm == nullptr)
	    return;

	this->exp1->OneStep();
	this->exp2->OneStep();

	tuner.Active = this->axeController->tunerEngaged();

	lm->CurrentLayout()->ProcessOutstanding();
	this->axeController->Update();
	lm->CurrentLayout()->RefreshScreens(currentPreset, tuner);	
}

void WorkerProcess::PrintDebug() {
	auto lm = GetLayoutManager();
	if (lm == nullptr)
		return;

	lm->CurrentLayout()->PrintDebug();
}