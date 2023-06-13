#pragma once

#include "Train.h"


class CargoTrain : public Train 
{

public:

    CargoTrain(int priority_, int id_, int maxSpeed_);

    void setNextSignal(SemaphoreEnum nextSignal_);

    void run();

};