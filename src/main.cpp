
#include <iostream>
#include <vector>
#include <string>
#include <ncurses.h>
#include <ctime>
#include <cstdlib>
#include <thread>
#include <cmath>

#include "../include/gui/InfoBuffer.h"
#include "../include/gui/PromptWindow.h"
#include "../include/gui/Canva.h"
#include "../include/RouteElement.h"
#include "../include/Station.h"

#define TRAINS_NUM 69

void drawLine(fVec p1, fVec p2, char sign)
{
    fVec versor;
    versor.x = p2.x - p1.x;
    versor.y = p2.y - p1.y;

    float verLen = fsqrt(versor.x * versor.x + versor.y * versor.y);

    versor.x /= verLen;
    versor.y /= verLen;

    int i = 0;

    fVec pos = {p1.x, p1.y};
    while(i++ < int(verLen))
    {
        mvprintw(pos.y, pos.x, "%c", sign);

        pos.x += versor.x;
        pos.y += versor.y;
    }
}

void drawTracks(std::vector<Station *> stations)
{
    for(int i = 0; i < stations.size(); i++)
    {
        for(int j = 0; j < stations.size(); j++)
        {
            drawLine(stations[i]->getPosition(), stations[j]->getPosition(), '+');
        }
    }
}

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
    stations.push_back(new Station("Shitovaty", 5, 5));

    stations[0]->setPosition(15, 10);
    stations[1]->setPosition(50, 30);
    stations[2]->setPosition(80, 5);
    stations[3]->setPosition(90, 20);


    std::vector<Train*> trains;
    std::vector<std::thread> trainsThreads;

    Canva canva({5, 1}, {120, 35});
    InfoBuffer buffer({5, 36}, {120, 20});

    canva.addComponent(stations[0]);
    canva.addComponent(stations[1]);
    canva.addComponent(stations[2]);
    canva.addComponent(stations[3]);

    for(int i = 0; i < TRAINS_NUM; i++)
    {
        RouteElement rt;
        RouteElement rt2;
        RouteElement rt3;
        RouteElement rt4;
        rt.station = stations[0];
        rt.stopTime = rand() % 500 + 100;
        rt2.station = stations[1];
        rt2.stopTime = rand() % 100 + 500;
        rt3.station = stations[2];
        rt3.stopTime = rand() % 100 + 500;
        rt4.station = stations[3];
        rt4.stopTime = rand() % 100 + 500;

        if(i % 2 == 0)
            trains.push_back(new PassengerTrain(120, rand()%99+1, {rt, rt2, rt3, rt4}));
        else
            trains.push_back(new PassengerTrain(120, rand()%99+1, {rt4, rt3, rt2, rt}));
        
        trains[i]->setPosition(rand()%120, rand()%40);
        canva.addComponent(trains[i]);
    }

    std::thread leave = std::thread(&Station::leavingMechanism, stations[0]);
    std::thread leave2 = std::thread(&Station::leavingMechanism, stations[1]);
    std::thread leave3 = std::thread(&Station::leavingMechanism, stations[2]);
    std::thread leave4 = std::thread(&Station::leavingMechanism, stations[3]);

    std::thread arrive = std::thread(&Station::arrivingMechanism, stations[0]);
    std::thread arrive2 = std::thread(&Station::arrivingMechanism, stations[1]);
    std::thread arrive3 = std::thread(&Station::arrivingMechanism, stations[2]);
    std::thread arrive4 = std::thread(&Station::arrivingMechanism, stations[3]);

    std::thread route1 = std::thread(setFreeRoute, stations[0]);
    std::thread route2 = std::thread(setFreeRoute, stations[1]);
    std::thread route3 = std::thread(setFreeRoute, stations[2]);
    std::thread route4 = std::thread(setFreeRoute, stations[3]);


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
        drawTracks(stations);
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

