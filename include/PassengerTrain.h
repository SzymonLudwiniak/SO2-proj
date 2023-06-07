#pragma once

#include "Train.h"

class PassengerTrain : public Train
{
public:

    PassengerTrain(int priority_, int maxSpeed_);

    void setNextSignal(SemaphoreEnum nextSignal_);
    void setDriver(int driverID_);
    void setTrackAt(int trackAt_);

    int getTrackAt();
    int getID();

    void run();
private:

    int delay;

    int platform{-1};

};