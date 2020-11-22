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
    effect1          = 22,
    effect2          = 23,
    effect3 = 24,
    effect4 = 25,
    effect5 = 26,
    effect6 = 27,
    effect7 = 28,
    effect8 = 29,
    effect9 = 30,
    effect10 = 31,
    mute = 32,
    preset_select = 33,
    
    // Just to signal end of enum
    Last            = 999
};


const FunctionName layoutDefinitions[LAYOUTS][FS_ROWS][FS_COLS]
{
    {
        { FunctionName::layout_incr,  FunctionName::mute,  FunctionName::preset_decr,    FunctionName::preset_incr,    FunctionName::preset_display},
        { FunctionName::tuner_toggle,     FunctionName::scene_select_6,   FunctionName::scene_select_7, FunctionName::scene_select_8, FunctionName::tap_tempo },
        { FunctionName::scene_select_1,   FunctionName::scene_select_2,   FunctionName::scene_select_3, FunctionName::scene_select_4, FunctionName::scene_select_5}
    },
    {
        { FunctionName::layout_incr,  FunctionName::mute,  FunctionName::preset_decr,    FunctionName::preset_incr,    FunctionName::preset_display},
        { FunctionName::tuner_toggle,     FunctionName::effect6,   FunctionName::effect7, FunctionName::exp_1_toggle, FunctionName::tap_tempo },
        { FunctionName::effect1,   FunctionName::effect2,   FunctionName::effect3, FunctionName::effect4, FunctionName::effect5}
    }
};

#endif