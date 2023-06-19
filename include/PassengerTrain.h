#pragma once

#include "Train.h"

class PassengerTrain : public Train
{
public:

    PassengerTrain(int priority_, int maxSpeed_, std::vector<RouteElement> route_);

    void setNextSignal(SemaphoreEnum nextSignal_);
    void setDriver(int driverID_);
    void setTrackAt(int trackAt_);
    void setIsAllowedToLeave(bool isAllowedToLeave_);


    int getTrackAt();
    int getID();
    bool getIsAbleToLeave();


    void run();
private:

    int delay;

    int platform{-1};

};