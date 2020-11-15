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

void drawCentreString(Adafruit_GFX* canvas, const char* buf, int canvasWidth = screen_w, int canvasHeight = screen_h, int border_width = default_border_w, int border_height = default_border_h)
{
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
