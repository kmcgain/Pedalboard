#ifndef LAYOUT_DEFINITION_H
#define LAYOUT_DEFINITION_H

#include "constants.h"

#define FUNCTIONNAMES(F) \
    F(layout_select_1), \
    F(layout_select_2), \
    F(layout_incr),     \
    F(layout_decr),     \
    F(scene_select_1),  \
    F(scene_select_2),  \
    F(scene_select_3),  \
    F(scene_select_4),  \
    F(scene_select_5),  \
    F(scene_select_6),  \
    F(scene_select_7),  \
    F(scene_select_8),  \
    F(scene_decr),    	\
    F(scene_icnr),    	\
    F(exp_1_toggle),    \
    F(exp_2_toggle),    \
    F(tuner_toggle),    \
    F(tap_tempo),    	\
    F(preset_decr),     \
    F(preset_incr),     \
    F(preset_incr_10),  \
    F(preset_display),  \
    F(effect1),    		\
    F(effect2),    		\
    F(effect3),    		\
    F(effect4),    		\
    F(effect5),    		\
    F(effect6),    		\
    F(effect7),    		\
    F(effect8),    		\
    F(effect9),    		\
    F(effect10),    	\
    F(mute),    		\
    F(preset_select)   

// Create the Enums
#define F(e) e
enum FunctionName { FUNCTIONNAMES(F), NumFunctionNames };
#undef F

// Create the strings
#define F(s) #s
char* FunctionNameStrs[] = { FUNCTIONNAMES(F) };
#undef F

FunctionName functionNameFromString(const char* s)
{
    for (auto i = 0; i < FunctionName::NumFunctionNames; i++) {
        if (strcmp(s, FunctionNameStrs[i]) == 0) {
            return static_cast<FunctionName>(i);
        }
    }

#ifdef TEST
        throw std::runtime_error("Bad function defintion");
#endif
    return static_cast<FunctionName>(0);
}

#endif

