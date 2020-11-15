#include "../Domain/screen_factory.h"
#include "Display/tft_screen.h"

Screen* ScreenFactory::CreateScreen(char screenNumber) {
	return new TftScreen(screenNumber);
}
