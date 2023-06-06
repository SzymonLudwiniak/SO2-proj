#include <iostream>
#include <vector>
#include <string>
#include <ncurses.h>
#include <ctime>

#include "../include/gui/Canva.h"
#include "../include/gui/InfoBuffer.h"

int main()
{
    srand(time(NULL));
    InfoBuffer buffer({0, 0}, {60, 10});

    initscr();
    initColors();

    char ch = 0;
    do
    {
        buffer.pushMessage("hello log " + std::to_string(ch), (rand()%3)+3);     
        buffer.draw();
    } while((ch = getch()) != 'q');

    endwin();
    return 0;
}
