#include "../Domain/screen_factory.h"
#include "tft_screen.h"

Screen* ScreenFactory::CreateScreen(int screenNumber) {
	return new TftScreen(screenNumber);
}
