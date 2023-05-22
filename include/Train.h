#pragma once

#include <string>
#include <thread>

class Train
{



protected:

    int priority;
    int id;
    int maxSpeed;
    int currentSpeed {0};


    std::string* route;

    std::thread trainThread;

};