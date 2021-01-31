void displayPresetSelect(TFT_eSPI* screen, FunctionState* state, int screenNumber) {  
    PresetFullSelectState* st = static_cast<PresetFullSelectState*>(state);
    auto selector = st->GetPresetSelector();

    if (screenNumber == 14) { // last button... todo: factor out
        // dislay back button
        screen->fillScreen(TFT_RED);
        screen->setTextColor(TFT_WHITE);
	    drawCentreString(screen, "Back");	
        return;
    }

    screen->fillScreen(TFT_RED);
    auto min = selector->MinForSegment(screenNumber);
    
    if (min == -1) {
        // blank
        return;
    }

    auto max = selector->MaxForSegment(screenNumber);
    if (min == max) {
        // single display
        screen->setTextColor(TFT_WHITE);
        sprintf(screenMessage, "%d", min);
	    drawCentreString(screen, screenMessage);	
        return;
    }

    auto numOnScreen = max-min+1;
    if (numOnScreen <= 3) {
        for (int i = 0; i < numOnScreen; i++) {
            auto canvasHeight = screen_h / numOnScreen;
            // GFXcanvas1 canvas(screen_w, canvasHeight);
            auto sprite = TFT_eSprite(screen);
            sprite.setColorDepth(8);
            sprite.createSprite(screen_w, canvasHeight);
            sprite.fillSprite(TFT_RED);
            sprite.setTextSize(3);
		    sprite.setTextFont(2);
            sprite.setTextColor(TFT_WHITE);

            sprintf(screenMessage, "%d", min+i);
            drawCentreString(&sprite, screenMessage, screen_w, canvasHeight, 2, 2);
            sprite.pushSprite(0, i* canvasHeight);            
        }
    }
    else {
        screen->setTextColor(TFT_WHITE);
        sprintf(screenMessage, "%d-%d", min, max);
	    drawCentreString(screen, screenMessage);	
    }
}