// layout_setup.h
#pragma once

#ifndef _LAYOUT_SETUP_h
#define _LAYOUT_SETUP_h

#include "layout_manager.h"

LayoutManager* GetLayoutManager();
void registerLayoutManager(LayoutManager* layoutManager);

#endif

