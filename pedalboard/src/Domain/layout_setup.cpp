#include "pch.h"
#include "layout_setup.h"

LayoutManager* layoutMgr = nullptr;

LayoutManager* GetLayoutManager() {
	return layoutMgr;
}

void registerLayoutManager(LayoutManager* layoutManager) {
	layoutMgr = layoutManager;
}