const char *jsonSettings = R""""(
{
    "expressionNames": [
        "Wah",
        "Volume",
        "Pitch"
    ],
    "buttonPins": [
        3,  5,  6,  7,  9, 
        22, 11, 12, 13, 24, 
        27, 26, 25, 28, 23 
    ],
    "screenPins": [
        34, 36, 40, 42, 43,
        41, 37, 35, 33, 45,
        48, 47, 46, 49, 44 
    ],
    "screenRotations": [
        1, 1, 1, 1, 1,
        1, 1, 1, 1, 3,
        1, 1, 1, 1, 1
    ],
    "layoutDefinitions": [
        [
            ["layout_incr",  "mute",  "preset_decr",    "preset_incr",    "preset_display"],
            ["tuner_toggle",     "scene_select_6",   "scene_select_7", "scene_select_8", "tap_tempo"],
            ["scene_select_1",   "scene_select_2",   "scene_select_3", "scene_select_4", "scene_select_5"]
        ],
        [
            ["layout_incr",  "mute",  "preset_decr",    "preset_incr",    "preset_display"],
            ["tuner_toggle",     "effect6",   "effect7", "exp_1_toggle", "tap_tempo"],
            ["effect1",   "effect2",   "effect3", "effect4", "effect5"]
        ]
    ]
}
)"""";
