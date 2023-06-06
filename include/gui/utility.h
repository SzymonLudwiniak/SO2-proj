#pragma once

#include <cstdint>

#define SCREENWIDTH 80
#define SCREENHEIGHT 60

#define BASE_COLOR      1
#define BORDER_COLOR    2
#define LOW_PRIO_COLOR  3
#define MID_PRIO_COLOR  4
#define TOP_PRIO_COLOR  5

#define LOW_PRIORITY 3
#define MID_PRIORITY 4
#define TOP_PRIORITY 5

void initColors();

struct sVec
{
    int x;
    int y;
};