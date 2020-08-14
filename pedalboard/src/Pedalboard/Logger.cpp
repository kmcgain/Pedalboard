#include "../Domain/logger.h"
#include <Arduino.h>

void Logger::log(const char msg[]) {
	Serial.print(msg);
}

void Logger::log(char* msg) {
	Serial.print(msg);
}

void Logger::log(char msg) {
	Serial.print(msg);
}

void Logger::log(int msg) {
	Serial.print(msg);
}

void Logger::log(unsigned int msg) {
	Serial.print(msg);
}

void Logger::log(long msg) {
	Serial.print(msg);
}

void Logger::log(unsigned long msg) {
	Serial.print(msg);
}

void Logger::log(double msg) {
	Serial.print(msg);
}