#pragma once

#include <math.h>

// TODO: We need to factor these into common place
#define max_preset 511
#define num_buttons 15

class PresetSelector {    
private:
    char level = 1;

    int presetsPerButton(char segment) {
        auto numberOfActivePresets = (Max-Min+1);
        double numActiveButtons = numberOfActivePresets < (num_buttons-1) ? numberOfActivePresets : (num_buttons-1);
        
        if (segment >= numActiveButtons) 
            return -1;

        return ceil(numberOfActivePresets / numActiveButtons);
    }

public:
    bool Active;
    int Min = 0;
    int Max = max_preset;

    bool IsLowestLevel() {
        return level == 1;
    }

    void Reset() {
        level = 1;
        Min = 0;
        Max = 511;
    }

    void Expand(char segment) {
        auto minForSegment = MinForSegment(segment);
        auto maxForSegment = MaxForSegment(segment);

        if (minForSegment == -1 || maxForSegment == -1)
            return;

        level++;
        Min = minForSegment;
        Max = maxForSegment;
    }

    int MinForSegment(char segment) {        
        auto perButton = presetsPerButton(segment);
        if (perButton == -1)
            return perButton;

        auto min = Min+(segment*perButton);
        if (min > Max)
            return -1;

        return min;
    } 

    int MaxForSegment(char segment) {
        auto perButton = presetsPerButton(segment);
        if (perButton == -1)
            return perButton;

        auto min = MinForSegment(segment);
        if (min == -1)
            return -1;
        auto max = min + perButton-1;
        return max > Max ? Max : max;
    } 
};