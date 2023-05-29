#include <iostream>
#include <vector>
#include <ncurses.h>

#include "../include/gui/Canva.h"

int main()
{
    Canva canva({0, 0}, {30, 20});
    Drawable a;
    a.setPosition(5, 5);

    initscr();

    endwin();
    return 0;
}
