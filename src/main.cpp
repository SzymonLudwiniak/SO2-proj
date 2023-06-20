
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
            fVec p1 = stations[i]->getPosition();
            fVec p2 = stations[j]->getPosition();
            p1.x +=1.0;
            p1.y +=1.0;
            p2.x +=1.0;
            p2.y +=1.0;

            drawLine(p1, p2, '+');
        }
    }
}

[[noreturn]] void setFreeRoute(Station * station)
{
    std::mutex m;
    while(true)
    {
        while(!station->getIsRouteFree()) {}

        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        std::lock_guard<std::mutex> lock(m);
        station->setIsRouteFree(true);
        m.unlock();
    }
}

int main()
{
    srand(time(nullptr));

    std::cout << "Type number of trains: \n";
    std::cin >> TRAINS_NUM;

    STATION_NUM = 5;

    std::vector<Station *> stations(STATION_NUM);
    std::vector<Train *> trains(TRAINS_NUM);
    std::vector<std::thread> stationThreads(STATION_NUM * 2); // both leaving and arriving
    std::vector<std::thread> trainThreads(TRAINS_NUM);
    std::vector<std::thread> freeingRouteThreads(STATION_NUM);
    std::vector<std::thread> trainsThreads(TRAINS_NUM);

    stations[0] = new Station("Wlodawa", 4, 4);
    stations[0]->setPosition(5, 10);
    stations[1] = new Station("Zary", 2, 2);
    stations[1]->setPosition(60, 7);
    stations[2] = new Station("Twardogora", 3, 3);
    stations[2]->setPosition(100, 12);
    stations[3] = new Station("Malin", 2, 2);
    stations[3]->setPosition(35, 27);
    stations[4] = new Station("Raciborz", 4, 4);
    stations[4]->setPosition(81, 30);

    Canva canva({7, 1}, {120, 35});
    InfoBuffer buffer({7, 36}, {120, 20});

    // creating stations
    for(int i = 0; i < STATION_NUM; i++)
    {
        canva.addComponent(stations[i]);
    }

    // creating trains
    for(int i = 0, k = 0; i < TRAINS_NUM; i++, k++)
    {

        std::vector<RouteElement> route(STATION_NUM);

        // creating routes
        for(int j = 0; j < STATION_NUM; j++)
        {
            RouteElement rt;
            rt.station = stations[(j + k) % STATION_NUM];
            rt.stopTime = rand() % 1000 + 1000;
            route[j] = rt;
        }

        trains[i] = new PassengerTrain(100, rand() % 20 + 100, route);
        
        auto pos = route[0].station->getPosition();
        pos.x -= 6.f;
        // pos.y -= 1.f;
        trains[i]->setPosition(pos);
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
    // for(int i = 0; i < STATION_NUM; i++)
    // {
    //     freeingRouteThreads[i] = std::thread(setFreeRoute, stations[i]);
    // }

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

