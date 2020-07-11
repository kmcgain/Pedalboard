#include "pch.h"
#include "worker_process.h"
#include "layout_setup.h"

void WorkerProcess::OneStep() {
	// Handle button presses
	GetLayoutManager()->CurrentLayout()->ProcessOutstanding();

	// Handle screen updates (lower priority)
}