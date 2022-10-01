#pragma once

#define WINDOW_TITLE "Snow simulator"
#define SCREEN_WIDTH 720
#define SCREEN_HEIGHT 480
#define MAX_SNOWFLAKES 150000
#define RANDOM_START_X rand()/(double)RAND_MAX * SCREEN_WIDTH
#define RANDOM_START_Y rand()/(double)RAND_MAX * (SCREEN_HEIGHT + 10) - 10