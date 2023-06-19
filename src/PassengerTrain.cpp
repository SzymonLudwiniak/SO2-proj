#include "../include/PassengerTrain.h"
#include <iostream>
#include <thread>
#include <chrono>

PassengerTrain::PassengerTrain(int priority_,int maxSpeed_, std::vector<RouteElement> route_)
{
    this->priority = priority_;
    this->id = trainCounter++;
    this->maxSpeed = maxSpeed_;
    this->route = route_;
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

bool PassengerTrain::getIsAbleToLeave()
{
    return isAbleToLeave;
}

void PassengerTrain::setDriver(int driverID_)
{
    this->driverID = driverID_;
}

void PassengerTrain::setTrackAt(int trackAt_)
{
    this->trackAt = trackAt_;
}

void PassengerTrain::setIsAllowedToLeave(bool isAllowedToLeave_)
{
    this->isAllowedToLeave = isAllowedToLeave_;
}

void PassengerTrain::run()
{
    while(this->stationCounter < (int) route.size())
    {

        // if no driver, train waits for the driver
        //while(driverID == -1){}

        // jest na trasie, semafory mu ustalaja predkosc
        if(nextSignal == SemaphoreEnum::STOP)
            currentSpeed = 0;
        else if(nextSignal == SemaphoreEnum::GO_40KMH)
            currentSpeed = 40;
        else
            currentSpeed = maxSpeed;


        // sjesli jest na trasie to pomija mechanizm wymiany pasazerów
        if(this->trackAt == -1)
            continue;

        std::this_thread::sleep_for(std::chrono::milliseconds(route[stationCounter].stopTime));

        std::cout << "Train " << id << " stopped at " << route[stationCounter].stationName << " for " << route[stationCounter].stopTime << "\n";


        while(!this->isAllowedToLeave) {}

        std::cout << "Train " << getID() << " left from track: " << getTrackAt() << "\n";

        this->trackAt = -1;
        this->isAllowedToLeave = false;
        this->stationCounter++;

    }

     std::cout << "Train: " << id << " finished its route.\n";
}