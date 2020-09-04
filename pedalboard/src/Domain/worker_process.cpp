#include "pch.h"
#include "worker_process.h"
#include "layout_setup.h"

void WorkerProcess::OneStep() {
	// Handle button presses
	auto lm = GetLayoutManager();
	if (lm == nullptr)
	    return;

	lm->CurrentLayout()->ProcessOutstanding();
	lm->CurrentLayout()->RefreshScreens();
	// Handle screen updates (lower priority)
}

void WorkerProcess::PrintDebug() {
	auto lm = GetLayoutManager();
	if (lm == nullptr)
		return;

	lm->CurrentLayout()->PrintDebug();
}