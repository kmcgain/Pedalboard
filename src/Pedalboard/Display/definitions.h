#define screen_w 160
#define screen_h 128
#define font_w_px 6
#define font_h_px 8
#define default_border_w 10
#define default_border_h 10

// Due pin 8 is hardwired to SPI RESET
#define rst_pin 8
// A0/DC
#define dc_pin 53

byte screen_pins[] = {
	34, 36, 40, 42, 43,
	41, 37, 35, 33, 45,
	48, 47, 46, 49, 44 
};
#define screenToRotate 9
