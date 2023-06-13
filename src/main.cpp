#include "../include/Station.h"

#include <thread>
#include <time.h>
#include <iostream>
#include <cstdlib>

#define TRAINS_NUM 5


[[noreturn]] void routeFreeTh(Station* st)
{
    while(true)
    {
        while(st->getIsRouteFree()) {}

        std::this_thread::sleep_for(std::chrono::milliseconds(4000));

        st->setIsRouteFree(true);
    }

}

int main()
{
    srand(time(nullptr));

    std::vector<Train> trains;

    RouteElement rt;

    Station st("modes", 3, 2);

    std::vector<Train*> passTrains(TRAINS_NUM, nullptr);

    for(int i = 0; i < TRAINS_NUM; i++)
    {
        RouteElement rt;
        rt.stationName = "modes";
        rt.stopTime = rand() % 4000 + 1000;


        passTrains[i] = new PassengerTrain(100, 120, {rt});
        st.addTrain(passTrains[i]);
    }

    std::vector<std::thread> passTrainsThreads;

    std::thread stationThLeave = std::thread(&Station::leavingMechanism, &st);
    std::thread stationThArrive = std::thread(&Station::arrivingMechanism, &st);

    std::thread setRouteFreeTH = std::thread(routeFreeTh, &st);

    for(int i = 0; i < TRAINS_NUM; i++)
    {
        passTrainsThreads.emplace_back(&Train::run, passTrains[i]);
    }



    stationThLeave.join();
    stationThArrive.join();

    for(int i = 0; i < TRAINS_NUM; i++)
    {
        passTrainsThreads[i].join();
    }

    setRouteFreeTH.join();

    return 0;
}

