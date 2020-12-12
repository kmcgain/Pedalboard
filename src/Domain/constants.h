#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "pch.h"

#define MAX_DIGITAL_PIN 53
#define FS_ROWS 3
#define FS_COLS 5

struct BoardConstants {
	byte Rising;
	byte Falling;
	byte Change;
};

#endif