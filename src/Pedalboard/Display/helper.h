#pragma once
char screenMessage[50];

void lengthOfLongestWord(const char* buf, byte& longestLength, byte& numWords) {
	byte currentLen = 0;
	byte index = 0;
	numWords = 1;
	longestLength = 0;

	while (true) {
		if (buf[index] == '\0')
			break;

		if (buf[index] == ' ' || buf[index] == '\n') {
			numWords++;
			if (currentLen > longestLength)
				longestLength = currentLen;
			currentLen = 0;
		}
		else
			currentLen++;

		index++;
	}

	if (currentLen > longestLength)
		longestLength = currentLen;
}


// #define TL_DATUM 0 // Top left (default)
// #define TC_DATUM 1 // Top centre
// #define TR_DATUM 2 // Top right
// #define ML_DATUM 3 // Middle left
// #define CL_DATUM 3 // Centre left, same as above
// #define MC_DATUM 4 // Middle centre
// #define CC_DATUM 4 // Centre centre, same as above
// #define MR_DATUM 5 // Middle right
// #define CR_DATUM 5 // Centre right, same as above
// #define BL_DATUM 6 // Bottom left
// #define BC_DATUM 7 // Bottom centre
// #define BR_DATUM 8 // Bottom right
// #define L_BASELINE  9 // Left character baseline (Line the 'A' character would sit on)
// #define C_BASELINE 10 // Centre character baseline
// #define R_BASELINE 11 // Right character baseline


int charsPerLine(TFT_eSPI* canvas) {
	const int fontWidth = canvas->textWidth("A");
	
	const int totalScreenWidth = 160;

	auto charsPerLine = totalScreenWidth / fontWidth;
	return charsPerLine;
}

void takeLine(TFT_eSPI* canvas, char* buf, const char* wholeString, int line) {
	int perLine = charsPerLine(canvas);
	int charOffset = line * perLine;

	int i = 0;
	for (i = 0; i < perLine; i++) {
		if (wholeString[charOffset + i] == '\0')
			break;

		buf[i] = wholeString[charOffset + i];
	}

	buf[i] = '\0';	
}


void drawCentreString(TFT_eSPI* canvas, const char* buf, int canvasWidth = screen_w, int canvasHeight = screen_h, int border_width = default_border_w, int border_height = default_border_h)
{
	canvas->setTextDatum(MC_DATUM);

	canvas->drawString(buf, canvasWidth/2, canvasHeight/2);
}

void drawCentreStringNew(TFT_eSPI* canvas, const char* buf, int canvasWidth = screen_w, int canvasHeight = screen_h, int border_width = default_border_w, int border_height = default_border_h)
{
	Logger::log("\nPRINT STR: ");
	Logger::log(buf);
	canvas->setTextDatum(TC_DATUM);

	int stringLength;
	while (buf[stringLength++] != '\0') {}
	stringLength--;

	Logger::log("\nSTR LEN: ");
	Logger::log(stringLength);
	char singleLineBuf[40];
	
	bool hasMore = true;
	int line = 0;
	while (hasMore) {
		takeLine(canvas, singleLineBuf, buf, line);
		auto y = 5 + (line * (canvas->fontHeight()));
		Logger::log("\nDRAW: ");
		Logger::log(singleLineBuf);

		canvas->drawString(singleLineBuf, canvasWidth/2, y);

		line++;
		hasMore = charsPerLine(canvas) * line < stringLength;

		Logger::log("\nCHARS PL: ");
		Logger::log(charsPerLine(canvas));
	}	
}

void drawTopCentreString(TFT_eSPI* canvas, const char* buf, int canvasWidth = screen_w, int canvasHeight = screen_h, int border_width = default_border_w, int border_height = default_border_h)
{
	drawCentreStringNew(canvas, buf, canvasWidth, canvasHeight, border_width, border_height);
}

/*void drawCentreString(TFT_eSPI* canvas, const char* buf, int canvasWidth = screen_w, int canvasHeight = screen_h, int border_width = default_border_w, int border_height = default_border_h)
{

	return;


	
	// Draw the string to fit on screen
	// Each font is 6x8 * font_size
	byte txtLength, numWords;
	lengthOfLongestWord(buf, txtLength, numWords);

	auto maxWidthOfFont = (canvasWidth - (border_width*2)) / (font_w_px*txtLength); 
	auto maxHeightOfFont = ((canvasHeight - (border_height*2)) / font_h_px) / numWords; // 1 word per line
	auto fontSize = maxWidthOfFont > maxHeightOfFont ? maxHeightOfFont : maxWidthOfFont;

	canvas->setTextSize(fontSize);

	byte bufIndex = 0;
	byte wordIndex = 0;
	byte wordNum = 0;
	while (buf[bufIndex] != '\0') {
		wordIndex = 0;
		wordNum++;

		while (buf[bufIndex] != '\0' && buf[bufIndex] != ' ' && buf[bufIndex] != '\n') {
			screenMessage[wordIndex++] = buf[bufIndex++];
		}
		if (buf[bufIndex] == ' ' || buf[bufIndex] == '\n') // skip over word separator
			bufIndex++;

		screenMessage[wordIndex] = '\0';
		
		auto text_width_px = fontSize * font_w_px * wordIndex;
		auto text_height_px = fontSize * font_h_px;
		auto x = (canvasWidth / 2) - (text_width_px / 2);
		auto y = ((wordNum * (canvasHeight)) / (numWords+1)) - (text_height_px / 2);
		canvas->setCursor(x, y);
		canvas->print(screenMessage);
	}	
}
*/