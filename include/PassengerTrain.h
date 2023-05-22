#pragma once

#include "Train.h"

class PassengerTrain : public Train
{
public:

    PassengerTrain(int priority_, int id_, int maxSpeed_);

    int getPriority() const;
    int getID() const;
    int getMaxSpeed() const;

    

private:

    int delay;



};