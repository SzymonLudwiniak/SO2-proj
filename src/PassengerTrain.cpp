#include "../include/PassengerTrain.h"
#include <iostream>

PassengerTrain::PassengerTrain(int priority_,int maxSpeed_)
{
    this->priority = priority_;
    this->id = trainCounter;
    this->maxSpeed = maxSpeed_;
}

void PassengerTrain::setNextSignal(SemaphoreEnum nextSignal_)
{
    nextSignal = nextSignal_;
}

int PassengerTrain::getTrackAt()
{
    return trackAt;
}

int PassengerTrain::getID()
{
    return id;
}

void PassengerTrain::setDriver(int driverID_)
{
    driverID = driverID_;
}

void PassengerTrain::setTrackAt(int trackAt_)
{
    trackAt = trackAt_;
}

void PassengerTrain::run()
{
    while(true)
    {
        
        // if no driver, train waits for the driver
        while(driverID == -1){}

        std::cout << "Driver is on" << "\n";

        if(nextSignal == SemaphoreEnum::STOP)
            currentSpeed = 0;
        else if(nextSignal == SemaphoreEnum::GO_40KMH)
            currentSpeed = 40;
        else
            currentSpeed = maxSpeed;
    }
}