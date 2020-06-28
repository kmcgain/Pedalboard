#include <AxeFxControl.h>

// #include "layout.h"
// #include "tape.h"

// RX1 Midi Input
// TX1 Midi Output

// A0 = 1/4" 1
// A1 = 1/4" 2

const int fs_rows = 3;
const int fs_cols = 5;

int fs_pins[fs_rows][fs_cols];
int tft_cs_pins[fs_rows][fs_cols];

//const int midi_in_pin = RX1;
//const int midi_out_pin = TX1;
const int exp_1_pin = A0;
const int exp_2_pin = A1;


const int tft_bl_pin = 52;
const int tft_sck_pin = SCK;
const int tft_sda_pin = SDA;
const int tft_a0_pin = 53; // TODO: Should this be analog pin instead?
const int tft_rst_pin = 51;

void init_pins() {  
  // Pins for switches/ screens arranged so they can grow towards each other over time (if I add more)
  
  // Footswitches - I'm growing from 0 up
  int pin_num = (fs_rows*fs_cols) - 1;
  for (int row = 0; row < fs_rows; row++) {
    for (int col = 0; col < fs_cols; col++) {
      fs_pins[row][col] = pin_num--;
    }
  }

  // Screen CS - I'm growing from 50 down
  pin_num = 50 - (fs_rows*fs_cols);
  for (int row = 0; row < fs_rows; row++) {
    for (int col = 0; col < fs_cols; col++) {
      tft_cs_pins[row][col] = pin_num++;
    }
  }


  // setup interrupts


}

/* Layouts, composed of any kind of button
 * Button kinds:  
 * Layout select / incr / decr
 * Scene select / incr / decr
 * Toggle exp pdl number
 * Tuner toggle
 * Bypass toggle (all effects)
 * 
 */


const int layout_select_1 = 0;
const int layout_select_2 = 1;
const int layout_incr     = 10;
const int layout_decr     = 11;
const int scene_select_1  = 20;
const int scene_select_2  = 21;
const int scene_select_3  = 22;
const int scene_select_4  = 23;
const int scene_select_5  = 24;
const int scene_select_6  = 25;
const int scene_select_7  = 26;
const int scene_select_8  = 27;
const int scene_decr      = 30;
const int scene_icnr      = 31;
const int exp_1_toggle    = 40;
const int exp_2_toggle    = 41;
const int tuner_toggle    = 50;
const int tap_tempo       = 51;
const int preset_decr     = 60;
const int preset_incr     = 61;
const int preset_incr_10  = 62;

const int layout_1_press[fs_rows][fs_cols]
{
  { layout_select_1,  layout_select_2,  preset_decr,    preset_incr,    preset_incr_10},
  { tuner_toggle,     scene_select_6,   scene_select_7, scene_select_8, tap_tempo },
  { scene_select_1,   scene_select_2,   scene_select_3, scene_select_4, scene_select_5}
};


void setup() {
  init_pins();

}

void loop() {
  // put your main code here, to run repeatedly:

}
