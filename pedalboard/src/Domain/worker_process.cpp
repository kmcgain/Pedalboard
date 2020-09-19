#include "pch.h"
#include "worker_process.h"
#include "layout_setup.h"
#include "preset.h"

WorkerProcess::WorkerProcess(AxeController* axeController) {
	this->axeController = axeController;
}

void WorkerProcess::OneStep(Preset* currentPreset) {
	// Handle button presses
	auto lm = GetLayoutManager();
	if (lm == nullptr)
	    return;

	lm->CurrentLayout()->ProcessOutstanding();
	this->axeController->Update();
	lm->CurrentLayout()->RefreshScreens(currentPreset);
	// Handle screen updates (lower priority)
}

void WorkerProcess::PrintDebug() {
	auto lm = GetLayoutManager();
	if (lm == nullptr)
		return;

	lm->CurrentLayout()->PrintDebug();
}