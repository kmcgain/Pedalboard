void displayPresetSelect(TFT_eSPI* screen, FunctionState* state, int screenNumber) {  
    PresetFullSelectState* st = static_cast<PresetFullSelectState*>(state);
    auto selector = st->GetPresetSelector();

    if (screenNumber == 3) {
        screen->fillScreen(TFT_BLACK);
        screen->setTextColor(TFT_GREEN);
        drawCentreString(screen, "Page -");	
        return;
    }
    if (screenNumber == 4) {
        screen->fillScreen(TFT_BLACK);
        screen->setTextColor(TFT_GREEN);
        drawCentreString(screen, "Page +");	
        return;
    }
    if (screenNumber == 14) {
        screen->fillScreen(TFT_BLACK);
        screen->setTextColor(TFT_GREEN);
	    drawCentreString(screen, "Back");
        return;	
    }

    // page 0 contains the current preset, pages are 12 presets 
    auto presetNumber = selector->NumberForPageAndScreen(screenNumber, st->CurrentPresetNumber());
    auto names = *st->AllPresetNames();
    auto presetToDisplay = names[presetNumber];

    if (st->CurrentPresetNumber() == presetNumber) {
        screen->fillScreen(TFT_RED);
        screen->setTextColor(TFT_WHITE);
    }
    else {
        screen->fillScreen(TFT_WHITE);
        screen->setTextColor(TFT_BLUE);
    }
    
    screen->setTextSize(2);
    
    char buf[MAX_PRESET_NAME_LENGTH+6];
    sprintf(buf, "%d - %s", presetNumber, presetToDisplay);
    // drawTopCentreString(screen, buf);	
    drawCentreStringNew(screen, buf);
}
