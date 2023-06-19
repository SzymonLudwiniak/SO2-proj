
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
    std::string STATION_NAMES[9] = {"Wlodawa", "Zary", "Twardogora", "Malin", "Raciborz", "Walbrzych",
    "Trzebnica", "Nowa Sol", "Dzialoszyn"};

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

    Canva canva({5, 1}, {120, 35});
    InfoBuffer buffer({5, 36}, {120, 20});

    // creating stations
    for(int i = 0; i < STATION_NUM; i++)
    {
        stations[i] = new Station(STATION_NAMES[i], rand() % 4 + 4, rand() % 2 + 2);
        stations[i]->setPosition(rand() % 118, rand() % 33 );
        canva.addComponent(stations[i]);
    }

    std::cout << "done stations\n";

    // creating trains
    for(int i = 0, k = 0; i < TRAINS_NUM; i++, k++)
    {
        int routeSize = rand() % STATION_NUM;

        if(routeSize < 2)
            routeSize = (routeSize + 3) % STATION_NUM;

        std::vector<RouteElement> route(routeSize);

        // creating routes
        for(int j = 0; j < routeSize; j++)
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

    std::cout << "done trains\n";

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

std::cout << "done stations threads\n";

    // creating freeing route threads
    for(int i = 0; i < STATION_NUM; i++)
    {
        freeingRouteThreads[i] = std::thread(setFreeRoute, stations[i]);
    }

    std::cout << "done statfreeingions\n";

    // creating train threads
    for(int i = 0; i < TRAINS_NUM; i++)
    {
        trainsThreads[i] = std::thread(&Train::run, trains[i]);
    }

std::cout << "done trains threads\n";

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

