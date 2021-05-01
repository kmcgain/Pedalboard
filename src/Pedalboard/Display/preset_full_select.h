void displayPresetSelect(TFT_eSPI* screen, FunctionState* state, int screenNumber) {  
    PresetFullSelectState* st = static_cast<PresetFullSelectState*>(state);
    auto selector = st->GetPresetSelector();

    if (screenNumber == 3) {
        screen->fillScreen(TFT_BLACK);
        screen->setTextColor(TFT_GREEN);
        screen->setTextSize(3);
        drawCentreString(screen, "Page -");	
        return;
    }
    if (screenNumber == 4) {
        screen->fillScreen(TFT_BLACK);
        screen->setTextColor(TFT_GREEN);
        screen->setTextSize(3);
        drawCentreString(screen, "Page +");	
        return;
    }
    if (screenNumber == 14) {
        screen->fillScreen(TFT_BLACK);
        screen->setTextColor(TFT_GREEN);
        screen->setTextSize(3);
	    drawCentreString(screen, "Back");
        return;	
    }

    // page 0 contains the current preset, pages are 12 presets 
    auto presetNumber = selector->NumberForPageAndScreen(screenNumber, st->CurrentPresetNumber());
    auto names = *st->AllPresetNames();
    auto presetToDisplay = names[presetNumber];

    if (st->CurrentPresetNumber() == presetNumber) {
        screen->fillScreen(COLOUR_FG_TITLE);
        screen->setTextColor(COLOUR_BG_PRIMARY);
    }
    else {
        screen->fillScreen(COLOUR_BG_PRIMARY);
        screen->setTextColor(COLOUR_FG_PRIMARY);
    }
    
    screen->setTextSize(2);
    
    char buf[MAX_PRESET_NAME_LENGTH+6];
    sprintf(buf, "%d - %s", presetNumber, presetToDisplay);
    // drawTopCentreString(screen, buf);	
    drawCentreStringNew(screen, buf);
}
