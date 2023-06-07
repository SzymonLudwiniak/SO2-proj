#pragma once

#include <string>
#include <vector>

#include "enums/SemaphoreEnum.h"


class Train
{
public:

    virtual void setNextSignal(SemaphoreEnum nextSignal_) = 0;
    virtual void run() = 0;

    virtual int getTrackAt() = 0;
    virtual int getID() = 0;
    
    virtual void setDriver(int driverID_) = 0;
    virtual void setTrackAt(int trackAt_) = 0;

protected:

    static int trainCounter;

    int priority;
    int id;
    int maxSpeed;
    int currentSpeed {0};
    int trackAt{-1};

    SemaphoreEnum nextSignal;

    std::vector<std::string> route;

    int driverID{-1};

};