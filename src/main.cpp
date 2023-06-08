/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  28.03.2023 12:22:10
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Szymon Ludwiniak (), szymon.ludwiniak4ti@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "../include/Station.h"

#include <thread>
#include <time.h>
#include <cstdlib>

#define TRAINS_NUM 5

int main()
{
    srand(time(nullptr));

    Station st("modes", 3, 2);

    std::vector<Train*> passTrains;

    for(int i = 0; i < TRAINS_NUM; i++)
    {
        RouteElement rt;
        rt.stationName = "modes";
        rt.stopTime = rand() % 4000 + 1000;


        passTrains.push_back(new PassengerTrain(100, 120, {rt}));
        st.addTrain(passTrains[i]);
    }

    std::vector<std::thread> passTrainsThreads;

    std::thread stationThLeave = std::thread(&Station::leavingMechanism, &st);
    std::thread stationThArrive = std::thread(&Station::arrivingMechanism, &st);

    for(int i = 0; i < TRAINS_NUM; i++)
    {
        passTrainsThreads.push_back(std::thread(&Train::run, &(*(passTrains[i]))));
    }


    stationThLeave.join();
    stationThArrive.join();
    
    for(int i = 0; i < TRAINS_NUM; i++)
    {
        passTrainsThreads[i].join();
    }

    return 0;
}
