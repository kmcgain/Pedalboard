#include "helper.h"
#include "colours.h"

#define __LOAD_IMAGES__

#ifdef __LOAD_IMAGES__
#include "./images/chorus.h"
#include "./images/compressor.h"
#include "./images/delay.h"
#include "./images/drive.h"
// #include "./images/enhance.h"
#include "./images/filter.h"
#include "./images/flange.h"
#include "./images/formant.h"
// #include "./images/gate.h"
#include "./images/graphicEq.h"
// #include "./images/irPlayer.h"
// #include "./images/looper.h"
// #include "./images/megaTap.h"
// #include "./images/mixer.h"
#include "./images/multiBandCompressor.h"
#include "./images/multiDelay.h"
// #include "./images/multiplexer.h"
#include "./images/panTrim.h"
#include "./images/parametricEq.h"
#include "./images/phaser.h"
#include "./images/pitch.h"
// #include "./images/plexDelay.h"
// #include "./images/resonator.h"
#include "./images/reverb.h"
#include "./images/ringMod.h"
#include "./images/rotary.h"
// #include "./images/synth.h"
// #include "./images/tanTap.h"
// #include "./images/toneMatch.h"
#include "./images/vocoder.h"
// #include "./images/volPan.h"
#include "./images/wah.h"
// #include "./images/x-over.h"
// #include "./images/send.h"
// #include "./images/return.h"
#endif


const uint16_t* image(const char* effect) {
#ifdef __LOAD_IMAGES__
	if (effect[0] == 'C' && effect[1] == 'M' && effect[2] == 'P')
		return compressorImg;
	else if (effect[0] == 'G' && effect[1] == 'E' && effect[2] == 'Q')
		return graphicEqImg;
	else if (effect[0] == 'P' && effect[1] == 'E' && effect[2] == 'Q')
		return parametricEqImg;
	else if (effect[0] == 'R' && effect[1] == 'E' && effect[2] == 'V')
		return reverbImg;
	else if (effect[0] == 'D' && effect[1] == 'L' && effect[2] == 'Y')
		return delayImg;
	else if (effect[0] == 'M' && effect[1] == 'T' && effect[2] == 'D')
		return multiDelayImg;
	else if (effect[0] == 'C' && effect[1] == 'H' && effect[2] == 'O')
		return chorusImg;
	else if (effect[0] == 'F' && effect[1] == 'L' && effect[2] == 'G')
		return flangeImg;
	else if (effect[0] == 'R' && effect[1] == 'O' && effect[2] == 'T')
		return rotaryImg;
	else if (effect[0] == 'P' && effect[1] == 'H' && effect[2] == 'R')
		return phaserImg;
	else if (effect[0] == 'W' && effect[1] == 'A' && effect[2] == 'H')
		return wahImg;
	else if (effect[0] == 'F' && effect[1] == 'R' && effect[2] == 'M')
		return formantImg;
	else if (effect[0] == 'V' && effect[1] == 'O' && effect[2] == 'L')
		return panTrimImg;
	else if (effect[0] == 'P' && effect[1] == 'I' && effect[2] == 'T')
		return pitchImg;
	else if (effect[0] == 'F' && effect[1] == 'I' && effect[2] == 'L')
		return filterImg;
	else if (effect[0] == 'D' && effect[1] == 'R' && effect[2] == 'V')
		return driveImg;	

	return NULL;

#else
	return NULL;
#endif
}


void effect(TFT_eSPI* screen, FunctionState* state, Preset* currentPreset) {
	EffectState* st = static_cast<EffectState*>(state);

	if (st->Name() != "") {
		const uint16_t* img = image(st->Name());
		if (img == NULL) {
			screen->fillScreen(!st->Bypassed() ? COLOUR_FG_TITLE : COLOUR_BG_PRIMARY);	
			screen->setTextColor(!st->Bypassed() ? COLOUR_BG_PRIMARY : COLOUR_FG_TITLE);
			drawCentreString(screen, st->Name());

			return;
		}

		screen->fillScreen(!st->Bypassed() ? COLOUR_FG_TITLE : COLOUR_BG_PRIMARY);

		screen->pushImage(15, 15, 128, 96, img);
	
		screen->drawRect(5, 5, 160-10, 128-10, !st->Bypassed() ? COLOUR_FG_TITLE : COLOUR_BG_PRIMARY);
		screen->drawRect(6, 6, 160-12, 128-12, !st->Bypassed() ? COLOUR_FG_TITLE : COLOUR_BG_PRIMARY);
	}
}
