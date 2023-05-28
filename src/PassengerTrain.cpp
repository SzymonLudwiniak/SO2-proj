#include "../include/PassengerTrain.h"

PassengerTrain::PassengerTrain(int priority_, int id_, int maxSpeed_)
{
    this->priority = priority_;
    this->id = id_;
    this->maxSpeed = maxSpeed_;

}

void PassengerTrain::setNextSignal(SemaphoreEnum nextSignal_)
{
    this->nextSignal = nextSignal_;
}

void PassengerTrain::run()
{
    
}