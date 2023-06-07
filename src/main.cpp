#include <iostream>
#include <vector>
#include <string>
#include <ncurses.h>
#include <ctime>

#include "../include/gui/Canva.h"
#include "../include/gui/InfoBuffer.h"
#include "../include/gui/PromptWindow.h"

int main()
{
    srand(time(NULL));
    Canva canva({20, 15}, {60, 20});
    InfoBuffer buffer({20, 5}, {60, 10});
    Drawable obj;
    obj.setPosition(0, 0);
    canva.addComponent(&obj);

    WINDOW * w = initscr();
    mousemask(ALL_MOUSE_EVENTS, NULL);
    mouseinterval(0);
    initColors();
    keypad(w, TRUE);
    noecho();   

    PromptWindow prompt({2, 2},{10, 5});
    prompt.setString("arek\njest\ngejem");
    MEVENT mEvent;
    int ch = 0;
    do
    {   
        clear();
        buffer.draw();
        canva.draw();
        prompt.draw();  
        if(ch == KEY_MOUSE && getmouse(&mEvent) == OK)
        {
            sVec objPos = obj.getPosition();
            sVec bufSize = buffer.getSize();
            if((mEvent.bstate & BUTTON1_PRESSED) && 
                mEvent.x == objPos.x && mEvent.y == objPos.y)
            {
                prompt.setVisible(true);
            }
            else
            {
                prompt.setVisible(false);
            }
        }
    } while((ch = getch()) != 'q');

    endwin();

    return 0;
}
