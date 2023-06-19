
#include <iostream>
#include <vector>
#include <string>
#include <ncurses.h>
#include <ctime>
#include <cstdlib>
#include <thread>

#include "../include/gui/Canva.h"
#include "../include/gui/InfoBuffer.h"
#include "../include/gui/PromptWindow.h"
#include "../include/Station.h"

#define TRAINS_NUM 5

[[noreturn]] void setFreeRoute(Station * station)
{
    while(true)
    {
        while(!station->getIsRouteFree()) {}

        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
        station->setIsRouteFree(true);
    }
}

int main()
{
    srand(time(nullptr));
    Station * station = new Station("modes", 2, 3);

    std::vector<Train*> trains;
    std::vector<std::thread> trainsThreads;

    for(int i = 0; i < TRAINS_NUM; i++)
    {
        RouteElement rt;
        rt.station = station;
        rt.stopTime = rand() % 1000;

        trains.push_back(new PassengerTrain(120, 120, {rt}));
        station->addTrain(trains[i]);
    }

    std::thread leave = std::thread(&Station::leavingMechanism, station);

    std::thread arrive = std::thread(&Station::arrivingMechanism, station);

    std::thread route = std::thread(setFreeRoute, station);

    for(int i = 0; i < TRAINS_NUM; i++)
    {
        trainsThreads.emplace_back(&Train::run, trains[i]);
    }

    // route.join();
    // leave.join();
    // arrive.join();


    // for(int i = 0; i < TRAINS_NUM; i++)
    // {
    //     trainsThreads[i].join();
    // }

    
    Canva canva({20, 15}, {60, 20});
    InfoBuffer buffer({20, 5}, {60, 10});
    Drawable obj;
    obj.setPosition(0, 0);
    canva.addComponent(&obj);

    for(int i = 0; i < TRAINS_NUM; i++)
    {
        auto train = trains[i];
        train->setPosition(i + i, i + i);
        canva.addComponent(train);
    }

    // this is for ncurses initialization
    WINDOW * w = initscr();
    mousemask(ALL_MOUSE_EVENTS, NULL);
    mouseinterval(0);
    initColors();
    keypad(w, TRUE);
    noecho();
    //////////////////////////////////////

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

