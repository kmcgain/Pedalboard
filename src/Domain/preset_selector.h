#pragma once

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

    bool IsMax() {
        return level == 2;
    }

    void Reset() {
        level = 1;
        Min = 0;
        Max = 511;
    }

    void Expand(char segment) {
        if (segment > (Max-Min))
            return;

        double numActiveOptions = (Max-Min+1) < (num_buttons-1) ? (Max-Min+1) : (num_buttons-1);

        int startOfNewRange = (int)((((segment+1)/numActiveOptions) * (Max-Min+1)) + Min - 1);


        auto newMin = MinForSegment(segment);
        if (newMin == -1)
            return;
        level++;
        Min = newMin;
        Max = Min + ((max_preset+1) / ((num_buttons-1) ^ level));
    }

    int MinForSegment(char segment) {        
        auto perButton = presetsPerButton(segment);
        if (perButton == -1)
            return perButton;

        auto min = segment*perButton;
        if (min > Max)
            return -1;

        return min;
    } 

    int MaxForSegment(char segment) {
        auto perButton = presetsPerButton(segment);
        if (perButton == -1)
            return perButton;

        auto max = MinForSegment(segment) + perButton-1;
        return max > Max ? Max : max;
    } 
};