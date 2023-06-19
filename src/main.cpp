
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
#include "../include/RouteElement.h"
#include "../include/Station.h"

#define TRAINS_NUM 3


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
    Station * station1 = new Station("modes", 2, 3);
    Station * station2 = new Station("modes", 2, 3);

    station1->setPosition(10, 10);
    station2->setPosition(50, 30);


    std::vector<Train*> trains;
    std::vector<std::thread> trainsThreads;

    Canva canva({5, 5}, {120, 40});

    canva.addComponent(station1);
    canva.addComponent(station2);

    for(int i = 0; i < TRAINS_NUM; i++)
    {
        RouteElement rt;
        RouteElement rt2;
        rt.station = station1;
        rt.stopTime = rand() % 1000;
        rt2.station = station2;
        rt.stopTime = rand() % 1000;

        trains.push_back(new PassengerTrain(120, rand()%99+1, {rt, rt2}));
        trains[i]->setPosition(rand()%120, rand()%40);
        canva.addComponent(trains[i]);
    }

    std::thread leave = std::thread(&Station::leavingMechanism, station1);

    std::thread arrive = std::thread(&Station::arrivingMechanism, station1);

    std::thread route = std::thread(setFreeRoute, station1);

    for(int i = 0; i < TRAINS_NUM; i++)
    {
        trainsThreads.emplace_back(&Train::run, trains[i]);
    }


    // this is for ncurses initialization //
    WINDOW * w = initscr();
    mousemask(ALL_MOUSE_EVENTS, NULL);
    mouseinterval(0);
    initColors();
    keypad(w, TRUE);
    nodelay(w, TRUE);
    noecho();
    ////////////////////////////////////////

    int ch = 0;
    do
    {   
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        clear();
        canva.draw();
    // } while(ch++ < 20);
    } while((ch = getch()) != 'q');

    endwin();

    return 0;
}

