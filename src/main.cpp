#include <iostream>
#include <vector>
#include <ncurses.h>

#include "../include/gui/Canva.h"

int main()
{
    Canva canva({0, 0}, {60, 30});
    Drawable a;
    a.setPosition(5, 5);
    canva.addComponent(&a);

    initscr();
    char ch = 0;
    do
    {
        erase();
        switch(ch)
        {
        case 'a':
            a.moveBy(-1, 0);
            break;
        case 'w':
            a.moveBy(0, -1);
            break;
        case 'd':
            a.moveBy(+1, 0);
            break;
        case 's':
            a.moveBy(0, +1);
            break;
        default:
            break;
        }

        canva.draw();
    } while((ch = getch()) != 'q');
    endwin();
    return 0;
}
