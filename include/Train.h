#pragma once

#include <string>
#include <vector>
#include <thread>

#include "enums/SemaphoreEnum.h"


class Train
{
public:

    virtual void setNextSignal(SemaphoreEnum nextSignal_) = 0;
    virtual void run() = 0;

protected:

    int priority;
    int id;
    int maxSpeed;
    int currentSpeed {0};

    SemaphoreEnum nextSignal;

    std::vector<std::string> route;

    int driversID{-1};

    std::thread trainThread;

};