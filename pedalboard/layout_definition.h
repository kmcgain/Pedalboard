#ifndef LAYOUT_DEFINITION_H
#define LAYOUT_DEFINITION_H

#include "constants.h"

enum FunctionName {
    layout_select_1,
    layout_select_2,
    layout_incr,
    layout_decr,
    scene_select_1,
    scene_select_2,
    scene_select_3,
    scene_select_4,
    scene_select_5,
    scene_select_6,
    scene_select_7,
    scene_select_8,
    scene_decr,
    scene_icnr,
    exp_1_toggle,
    exp_2_toggle,
    tuner_toggle,
    tap_tempo,
    preset_decr,
    preset_incr,
    preset_incr_10,
    // Just to signal end of enum
    Last
};


const FunctionName layoutDefinitions[LAYOUTS][FS_ROWS][FS_COLS]
{
    {
        { FunctionName::layout_select_1,  FunctionName::layout_select_2,  FunctionName::preset_decr,    FunctionName::preset_incr,    FunctionName::preset_incr_10},
        { FunctionName::tuner_toggle,     FunctionName::scene_select_6,   FunctionName::scene_select_7, FunctionName::scene_select_8, FunctionName::tap_tempo },
        { FunctionName::scene_select_1,   FunctionName::scene_select_2,   FunctionName::scene_select_3, FunctionName::scene_select_4, FunctionName::scene_select_5}
    }
};

#endif