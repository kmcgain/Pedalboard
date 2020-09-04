#include "pch.h"
#include "../Domain/logger.h"
#include <iostream>

void Logger::log(const char msg[]) {
	std::cout << msg;
}

void Logger::log(char msg) {
	std::cout << msg;
}

void Logger::log(char* msg) {
	std::cout << msg;
}

void Logger::log(int msg) {
	std::cout << msg;
}

void Logger::log(unsigned int msg) {
	std::cout << msg;
}

void Logger::log(long msg) {
	std::cout << msg;
}

void Logger::log(unsigned long msg) {
	std::cout << msg;
}

void Logger::log(double msg) {
	std::cout << msg;
}

