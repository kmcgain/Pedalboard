#pragma once

#include "pch.h"
#include <math.h>

// TODO: We need to factor these into common place
#define max_preset 511
#define num_buttons 15

class PresetSelector {    
private:
    byte level = 1;

    int presetsPerButton(byte segment) {
        auto numberOfActivePresets = (Max-Min+1);
        double numActiveButtons = numberOfActivePresets < (num_buttons-1) ? numberOfActivePresets : (num_buttons-1);
        
        if (segment >= numActiveButtons) 
            return -1;

        return ceil(numberOfActivePresets / numActiveButtons);
    }

    int selectedPage = 0;

public:
    bool Active;
    int Min = 0;
    int Max = max_preset;

    bool IsLowestLevel() {
        return level == 1;
    }

    void PageReset() {
        selectedPage = 0;
    }

    void Reset() {
        level = 1;
        Min = 0;
        Max = 511;
    }

    int NumberForPageAndScreen(byte buttonNumber, int currentPresetNumber) {
        if (buttonNumber == 3 || buttonNumber == 4 || buttonNumber == 14)
            return -1;

        int numberOfPresetsPerPage = 12;
        int activePage = (currentPresetNumber / numberOfPresetsPerPage) + selectedPage;
        if (activePage < 0)
            activePage = 0;
        auto maxPage = (512/numberOfPresetsPerPage) - 1;
        if (activePage > maxPage)
            activePage = maxPage;

        auto startingPresetNumber = (numberOfPresetsPerPage * activePage);
        auto presetNumber = startingPresetNumber + buttonNumber;
        if (buttonNumber >= 5)
            presetNumber -= 2;
        return presetNumber;
    }

	int SelectedPage() {
		return selectedPage;
	}

	void PageUp() {
		selectedPage++;
	}

	void PageDown() {
		selectedPage--;
	}
};