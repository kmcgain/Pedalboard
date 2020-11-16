void displayPresetSelect(GFrame* screen, FunctionState* state, int screenNumber) {  
    PresetFullSelectState* st = static_cast<PresetFullSelectState*>(state);
    auto selector = st->GetPresetSelector();

    screen->beginDraw();

    if (screenNumber == 14) { // last button... todo: factor out
        // dislay back button
        screen->fillScreen(ST7735_RED);
        screen->setTextColor(ST7735_WHITE);
	    drawCentreString(screen, "Back");	
        screen->endDraw();
        return;
    }

    screen->fillScreen(ST7735_RED);
    auto min = selector->MinForSegment(screenNumber);
    
    if (min == -1) {
        // blank        
        sprintf(screenMessage, "\nScreen: %d - Min", screenNumber);
        Logger::log(screenMessage);
        screen->endDraw();
        return;
    }

    auto max = selector->MaxForSegment(screenNumber);
    if (min == max) {
        sprintf(screenMessage, "\nScreen Max: %d", min);
        Logger::log(screenMessage);
        // single display
        screen->setTextColor(ST7735_WHITE);
        sprintf(screenMessage, "%d", min);
	    drawCentreString(screen, screenMessage);	
        screen->endDraw();
        return;
    }

    sprintf(screenMessage, "\nMax (%d), Min (%d)", max, min);
    Logger::log(screenMessage);

    auto numOnScreen = max-min+1;
    if (numOnScreen <= 3) {
        for (int i = 0; i < numOnScreen; i++) {
            auto canvasHeight = screen_h / numOnScreen;
            GFXcanvas1 canvas(screen_w, canvasHeight);

            sprintf(screenMessage, "%d", min+i);
            drawCentreString(&canvas, screenMessage, screen_w, canvasHeight, 2, 2);
            screen->drawBitmap(0, i * canvasHeight, canvas.getBuffer(), 
                screen_w, canvasHeight,  
                ST7735_WHITE, 
                ST7735_RED);
        }
    }
    else {
        screen->setTextColor(ST7735_WHITE);
        sprintf(screenMessage, "%d - %d", min, max);
	    drawCentreString(screen, screenMessage);	
    }

    screen->endDraw();
}