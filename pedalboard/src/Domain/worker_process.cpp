#include "pch.h"
#include "worker_process.h"
#include "layout_setup.h"

void WorkerProcess::OneStep() {
	GetLayoutManager()->CurrentLayout()->ProcessOutstanding();
}