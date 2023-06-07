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
    Train* ps = new PassengerTrain(100, 120);

    st.addTrain(ps);
    std::thread tr = std::thread(&Train::run, &(*ps));

    std::thread stationTh = std::thread(&Station::run, &st);

    tr.join();
    stationTh.join();

    return 0;
}
