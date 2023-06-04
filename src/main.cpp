#include <iostream>
#include <vector>
#include <ncurses.h>

#include "../include/gui/Canva.h"

int main()
{
    Canva canva({0, 0}, {60, 30});
    Drawable a;
    a.setPosition(5, 5);

    initscr();
    canva.draw();
    getch();
    endwin();
    return 0;
}
