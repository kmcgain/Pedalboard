#include "../Domain/screen_factory.h"
#include "tft_screen.h"

Screen* ScreenFactory::CreateScreen(char screenNumber) {
	return new TftScreen(screenNumber);
}
