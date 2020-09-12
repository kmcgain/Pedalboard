#ifndef CONSTANTS_H
#define CONSTANTS_H

#define MAX_DIGITAL_PIN 53
#define FS_ROWS 3
#define FS_COLS 5
#define LAYOUTS 1

struct BoardConstants {
	unsigned char Rising;
	unsigned char Falling;
	unsigned char Change;
};

#endif