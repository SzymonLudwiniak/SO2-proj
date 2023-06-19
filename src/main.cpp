
#include <iostream>
#include <vector>
#include <string>
#include <ncurses.h>
#include <ctime>
#include <cstdlib>
#include <thread>

#include "../include/gui/InfoBuffer.h"
#include "../include/gui/PromptWindow.h"
#include "../include/gui/Canva.h"
#include "../include/RouteElement.h"
#include "../include/Station.h"

#define TRAINS_NUM 69


[[noreturn]] void setFreeRoute(Station * station)
{
    while(true)
    {
        while(!station->getIsRouteFree()) {}

        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        station->setIsRouteFree(true);
    }
}

int main()
{
    srand(time(nullptr));
    std::vector<Station *> stations;
    stations.push_back(new Station("modes", 4, 4));
    stations.push_back(new Station("dupaGolt", 3, 3));
    stations.push_back(new Station("WiadGej", 6, 6));

    stations[0]->setPosition(15, 10);
    stations[1]->setPosition(50, 30);
    stations[2]->setPosition(80, 5);


    std::vector<Train*> trains;
    std::vector<std::thread> trainsThreads;

    Canva canva({5, 1}, {120, 35});
    InfoBuffer buffer({5, 36}, {120, 20});

    canva.addComponent(stations[0]);
    canva.addComponent(stations[1]);
    canva.addComponent(stations[2]);

    for(int i = 0; i < TRAINS_NUM; i++)
    {
        RouteElement rt;
        RouteElement rt2;
        RouteElement rt3;
        rt.station = stations[0];
        rt.stopTime = rand() % 500 + 100;
        rt2.station = stations[1];
        rt2.stopTime = rand() % 100 + 500;
        rt3.station = stations[2];
        rt3.stopTime = rand() % 100 + 500;

        if(i % 2 == 0)
            trains.push_back(new PassengerTrain(120, rand()%99+1, {rt, rt2, rt3}));
        else
            trains.push_back(new PassengerTrain(120, rand()%99+1, {rt3, rt2, rt}));
        
        trains[i]->setPosition(rand()%120, rand()%40);
        canva.addComponent(trains[i]);
    }

    std::thread leave = std::thread(&Station::leavingMechanism, stations[0]);
    std::thread leave2 = std::thread(&Station::leavingMechanism, stations[1]);

    std::thread arrive = std::thread(&Station::arrivingMechanism, stations[0]);
    std::thread arrive2 = std::thread(&Station::arrivingMechanism, stations[1]);

    std::thread route1 = std::thread(setFreeRoute, stations[0]);
    std::thread route2 = std::thread(setFreeRoute, stations[1]);


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
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        clear();
        canva.draw();
        buffer.draw();

        MEVENT mEvent;

        if(getmouse(&mEvent) == OK)
        {
            for(auto d : stations)
            {
                fVec p = d->getPosition();
                if(mEvent.x == int(p.x) && mEvent.y == int(p.y))
                {
                    d->prompt.setVisible(true);
                }
                else
                {
                    d->prompt.setVisible(false);
                }
            }
        }
    } while((ch = getch()) != 'q');

    endwin();

    return 0;
}

