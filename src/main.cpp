
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

int TRAINS_NUM;
int STATION_NUM;

void drawLine(fVec p1, fVec p2, char sign)
{
    fVec versor;
    versor.x = p2.x - p1.x;
    versor.y = p2.y - p1.y;

    float verLen = sqrtf(versor.x * versor.x + versor.y * versor.y);

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

    std::cout << "Type number of trains: \n";
    std::cin >> TRAINS_NUM;

    std::cout << "Type number of station (1-9):\n";
    std::cin >> STATION_NUM;

    std::vector<Station *> stations(STATION_NUM);
    std::vector<Train *> trains(TRAINS_NUM);
    std::vector<std::thread> stationThreads(STATION_NUM * 2); // both leaving and arriving
    std::vector<std::thread> trainThreads(TRAINS_NUM);
    std::vector<std::thread> freeingRouteThreads(STATION_NUM);
    std::vector<std::thread> trainsThreads(TRAINS_NUM);

    stations[0] = new Station("Wlodawa", 8, 4);
    stations[0]->setPosition(5, 10);
    stations[1] = new Station("Zary", 4, 2);
    stations[1]->setPosition(60, 7);
    stations[2] = new Station("Twardogora", 6, 3);
    stations[2]->setPosition(100, 12);
    stations[3] = new Station("Malin", 8, 2);
    stations[3]->setPosition(35, 27);
    stations[4] = new Station("Raciborz", 8, 4);
    stations[4]->setPosition(81, 30);

    Canva canva({5, 1}, {120, 35});
    InfoBuffer buffer({5, 36}, {120, 20});

    // creating stations
    for(int i = 0; i < STATION_NUM; i++)
    {
        canva.addComponent(stations[i]);
    }

    // creating trains
    for(int i = 0, k = 0; i < TRAINS_NUM; i++, k++)
    {
        int routeSize = rand() % STATION_NUM;

        if(routeSize < 2)
            routeSize = (routeSize + 2) % STATION_NUM;

        std::vector<RouteElement> route(routeSize);

        // creating routes
        for(int j = 0; j < routeSize; j++, k++)
        {
            RouteElement rt;
            rt.station = stations[(j + k) % STATION_NUM];
            rt.stopTime = rand() % 1000 + 1000;
            route[j] = rt;
        }

        trains[i] = new PassengerTrain(rand() % 50, rand() % 20 + 100, route);
        
        auto pos = route[0].station->getPosition();

        trains[i]->setPosition(pos.x, pos.y);
        route[0].station->addTrain(trains[i]);
        canva.addComponent(trains[i]);
    }

    // creating station threads
    for(int i = 0, j = 0; i < STATION_NUM * 2; i++)
    {
        if(i % 2 == 0)
            stationThreads[i] = std::thread(&Station::arrivingMechanism, stations[j]);
        else
        {
            stationThreads[i] = std::thread(&Station::leavingMechanism, stations[j]);
            j++;
        }
    }

    // creating freeing route threads
    for(int i = 0; i < STATION_NUM; i++)
    {
        freeingRouteThreads[i] = std::thread(setFreeRoute, stations[i]);
    }

    // creating train threads
    for(int i = 0; i < TRAINS_NUM; i++)
    {
        trainsThreads[i] = std::thread(&Train::run, trains[i]);
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
        erase();
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

