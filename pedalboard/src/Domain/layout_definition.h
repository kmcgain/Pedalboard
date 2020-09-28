#ifndef LAYOUT_DEFINITION_H
#define LAYOUT_DEFINITION_H

#include "constants.h"

enum FunctionName {
    layout_select_1 = 0,
    layout_select_2 = 1,
    layout_incr     = 2,
    layout_decr     = 3,
    scene_select_1  = 4,
    scene_select_2  = 5,
    scene_select_3  = 6,
    scene_select_4  = 7,
    scene_select_5  = 8,
    scene_select_6  = 9,
    scene_select_7  = 10,
    scene_select_8  = 11,
    scene_decr      = 12,
    scene_icnr      = 13,
    exp_1_toggle    = 14,
    exp_2_toggle    = 15,
    tuner_toggle    = 16,
    tap_tempo       = 17,
    preset_decr     = 18,
    preset_incr     = 19,
    preset_incr_10  = 20,
    preset_display  = 21,
    // Just to signal end of enum
    Last            = 999
};


const FunctionName layoutDefinitions[LAYOUTS][FS_ROWS][FS_COLS]
{
    {
        { FunctionName::layout_select_1,  FunctionName::layout_select_2,  FunctionName::preset_decr,    FunctionName::preset_incr,    FunctionName::preset_display},
        { FunctionName::tuner_toggle,     FunctionName::scene_select_6,   FunctionName::scene_select_7, FunctionName::scene_select_8, FunctionName::tap_tempo },
        { FunctionName::scene_select_1,   FunctionName::scene_select_2,   FunctionName::scene_select_3, FunctionName::scene_select_4, FunctionName::scene_select_5}
    }
};

#endif