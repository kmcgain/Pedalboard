#include "../Domain/screen_factory.h"
#include "Display/tft_screen.h"

Screen* ScreenFactory::CreateScreen(byte screenNumber) {
	return new TftScreen(screenNumber);
}

void ScreenFactory::GlobalInit() {
	TftScreen::GlobalInit();
}
