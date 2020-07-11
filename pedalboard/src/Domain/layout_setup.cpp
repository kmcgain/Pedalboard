#include "pch.h"
#include "layout_setup.h"

LayoutManager* layoutMgr;

LayoutManager* GetLayoutManager() {
	return layoutMgr;
}

void registerLayoutManager(LayoutManager* layoutManager) {
	layoutMgr = layoutManager;
}