#pragma once

class Logger {
public:
    static void flush();
    static void log(const char[]);
    static void log(char*);
    static void log(char);
    static void log(int);
    static void log(unsigned int);
    static void log(long);
    static void log(unsigned long);
    static void log(double);
};
