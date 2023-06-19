#pragma once

#include "Train.h"


class CargoTrain : public Train 
{

public:

    CargoTrain(int priority_, int id_, int maxSpeed_);

    void setNextSignal(SemaphoreEnum nextSignal_);
    void setDriver(int driverID_);
    void setTrackAt(int trackAt_);

    int getTrackAt();
    int getID();

    void run();

};