#include "../include/CargoTrain.h"

CargoTrain::CargoTrain(int priority_, int id_, int maxSpeed_)
{
    this->priority = priority_;
    this->id = id_;
    this->maxSpeed = maxSpeed_;
}

void CargoTrain::setNextSignal(SemaphoreEnum nextSignal_)
{
    this->nextSignal = nextSignal_;
}

void CargoTrain::run()
{
    while(route.size())
    {
        if(nextSignal == SemaphoreEnum::STOP)
            currentSpeed = 0;
        else if(nextSignal == SemaphoreEnum::GO_40KMH)
            currentSpeed = 40;
        else
            currentSpeed = maxSpeed;
        
    }
}