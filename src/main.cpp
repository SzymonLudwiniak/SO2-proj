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

int main()
{
    Station st("modes", 3, 1);
    
    RouteElement rt;
    rt.stationName = "modes";
    rt.stopTime = 5000;



    Train* ps = new PassengerTrain(100, 120, {rt});

    st.addTrain(ps);
    std::thread tr = std::thread(&Train::run, &(*ps));

    std::thread stationThLeave = std::thread(&Station::leavingMechanism, &st);
    std::thread stationThArrive = std::thread(&Station::arrivingMechanism, &st);
    
    stationThLeave.join();
    stationThArrive.join();
    tr.join();

    return 0;
}
