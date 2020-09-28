#include "str_fn.h"

void strTerm(char* output, const char* src, short length) {
	short i = 0;
	bool lastWasSpace = false;

	if (src != nullptr)
		for (i = 0; i < length && src[i] != '\0'; i++) {
			if (lastWasSpace && src[i] == ' ') {
				i--; // otherwise we lead trailing space
				break;
			}

			lastWasSpace = src[i] == ' ';
			output[i] = src[i];
		}

	if (i == length)
		i--;
	output[i] = '\0';
}