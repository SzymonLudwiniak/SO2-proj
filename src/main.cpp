#include <iostream>
#include <vector>
#include <string>
#include <ncurses.h>

#include "../include/gui/Canva.h"
#include "../include/gui/InfoBuffer.h"

int main()
{
    InfoBuffer buffer({0, 0}, {60, 10});

    initscr();
    char ch = 0;
    getch();
    do
    {
        buffer.pushMessage("maciek jest gej! " + std::to_string(ch) + "potrzebna jest bardzo dluga wiadomosc!!!!dsaad");     
        buffer.draw();
    } while((ch = getch()) != 'q');

    endwin();
    return 0;
}
