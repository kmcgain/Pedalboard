#include "../Domain/logger.h"
#include <Arduino.h>
#include <String>

const int SIZE = 100;
String pending[SIZE];
int next = 0;

void Logger::flush() {
	for (int i = 0; i < next; i++)
		Serial.print(pending[i]);
	next = 0;
}

void Logger::log(const char msg[]) {
	if (next >= SIZE)
		return;
	pending[next++] = String(msg);
}

void Logger::log(char* msg) {
	if (next >= SIZE)
		return;
	pending[next++] = String(msg);
}

void Logger::log(char msg) {
	if (next >= SIZE)
		return;
	pending[next++] = String(msg);
}

void Logger::log(int msg) {
	if (next >= SIZE)
		return;
	pending[next++] = String(msg);
}

void Logger::log(unsigned int msg) {
	if (next >= SIZE)
		return;
	pending[next++] = String(msg);
}

void Logger::log(long msg) {
	if (next >= SIZE)
		return;
	pending[next++] = String(msg);
}

void Logger::log(unsigned long msg) {
	if (next >= SIZE)
		return;
	pending[next++] = String(msg);
}

void Logger::log(double msg) {
	if (next >= SIZE)
		return;
	pending[next++] = String(msg);
}