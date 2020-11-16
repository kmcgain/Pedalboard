#pragma once

// TODO: We need to factor these into common place
#define max_preset 511
#define num_buttons 15

class PresetSelector {    
private:
    char level = 1;

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

        int startOfNewRange = (((segment+1)/numActiveOptions) * (Max-Min+1)) + Min - 1;


        auto newMin = MinForSegment(segment);
        if (newMin == -1)
            return;
        level++;
        Min = newMin;
        Max = Min + ((max_preset+1) / ((num_buttons-1) ^ level));
    }

    int MinForSegment(char segment) {
        if (segment > (Max-Min))
            return -1;

        double numActiveOptions = (Max-Min+1) < (num_buttons-1) ? (Max-Min+1) : (num_buttons-1);

        int startOfNewRange = (((segment)/numActiveOptions) * (Max-Min+1)) + Min;        
        return startOfNewRange;
    } 

    int MaxForSegment(char segment) {
        auto max = MinForSegment(segment+1);
        return max > Max ? Max : max;
    } 
};