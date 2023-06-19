#include "../include/CargoTrain.h"

CargoTrain::CargoTrain(int priority_, int id_, int maxSpeed_)
{
    this->priority = priority_;
    this->id = id_;
    this->maxSpeed = maxSpeed_;
}

void CargoTrain::setNextSignal(SemaphoreEnum nextSignal_)
{
    nextSignal = nextSignal_;
}

int CargoTrain::getTrackAt()
{
    return trackAt;
}

int CargoTrain::getID()
{
    return id;
}

void CargoTrain::setDriver(int driverID_)
{
    driverID = driverID_;
}

void CargoTrain::setTrackAt(int trackAt_)
{
    trackAt = trackAt_;
}

void CargoTrain::run()
{
    while(true)
    {
        // if no driver, train waits for the driver
        while(driverID == -1){}

        if(nextSignal == SemaphoreEnum::STOP)
            currentSpeed = 0;
        else
            currentSpeed = maxSpeed;
    }
}
