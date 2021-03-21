#include "../Domain/logger.h"
#include <Arduino.h>

#define LOGGING_ON

const int SIZE = 30;
char pending[SIZE][50];
int next = 0;

// We use a flushing system to allow us to log during interrupts. Even logging when in an atomic block from main loop will cause
// crash due to interrupts being unavailable (for serial IO)
// We should only call flush from main loop outside atomic block
void Logger::flush() {
#ifdef LOGGING_ON	
	for (int i = 0; i < next; i++)
		Serial.print(pending[i]);
	next = 0;
#endif
}

void Logger::log(const char msg[]) {
#ifdef LOGGING_ON	
	if (next >= SIZE)
		return;
	sprintf(pending[next++], "%s", msg);
#endif
}

void Logger::log(char* msg) {
#ifdef LOGGING_ON	
	if (next >= SIZE)
		return;
	sprintf(pending[next++], "%s", msg);
#endif
}

void Logger::log(char msg) {
#ifdef LOGGING_ON	
	if (next >= SIZE)
		return;
	sprintf(pending[next++], "%s", msg);
#endif
}

void Logger::log(int msg) {
#ifdef LOGGING_ON	
	if (next >= SIZE)
		return;
	sprintf(pending[next++], "%d", msg);
#endif
}

void Logger::log(unsigned int msg) {
#ifdef LOGGING_ON	
	if (next >= SIZE)
		return;
	sprintf(pending[next++], "%d", msg);
#endif
}

void Logger::log(long msg) {
#ifdef LOGGING_ON	
	if (next >= SIZE)
		return;
	sprintf(pending[next++], "%d", msg);
#endif
}

void Logger::log(unsigned long msg) {
#ifdef LOGGING_ON	
	if (next >= SIZE)
		return;
	sprintf(pending[next++], "%d", msg);
#endif
}

void Logger::log(double msg) {
#ifdef LOGGING_ON	
	if (next >= SIZE)
		return;
	sprintf(pending[next++], "%d", msg);
#endif
}