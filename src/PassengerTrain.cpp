#include "../include/PassengerTrain.h"
#include "../include/RouteElement.h"
#include "../include/Station.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>



PassengerTrain::PassengerTrain(int priority_,int maxSpeed_, std::vector<RouteElement> route_)
{
    this->priority = priority_;
    this->id = trainCounter++;
    this->maxSpeed = maxSpeed_;
    this->route = route_;
}

RouteElement PassengerTrain::getFirstStation()
{
    return this->route[0];
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
        {
            currentSpeed = 0;
        }
        else
        {
            currentSpeed = maxSpeed;
            fVec pos = this->getPosition();
            std::this_thread::sleep_for(std::chrono::milliseconds(int(1/float(currentSpeed)*10000)));
            fVec vec;

            fVec stationPos = route[stationCounter].station->getPosition();
            stationPos.x += 1.f;
            stationPos.y += 1.f;

            vec = {stationPos.x - pos.x, stationPos.y - pos.y};

            float lenght = sqrtf(vec.x*vec.x + vec.y*vec.y);

            vec.x /= lenght;
            vec.y /= lenght;

            this->moveBy(vec);
        }

        fVec pos = this->getPosition();
        fVec stationPos = route[stationCounter].station->getPosition();
        stationPos.x += 1.f;
        stationPos.y += 1.f;
        if(!hasArrived && abs(pos.x-stationPos.x) < 1.f && abs(pos.y-stationPos.y) < 1.f)
        {
            InfoBuffer::getInstance()->pushMessage("train arrived on station: " + route[stationCounter].station->name, MID_PRIORITY);
            route[stationCounter].station->addTrain(this);
            hasArrived = true;
        }

        // sjesli jest na trasie to pomija mechanizm wymiany pasazerów
        if(this->trackAt == -1)
            continue;

        InfoBuffer::getInstance()->pushMessage("Train " + std::to_string(id) + " stopped for " + std::to_string(route[stationCounter].stopTime) + "\n", LOW_PRIORITY);
        std::this_thread::sleep_for(std::chrono::milliseconds(route[stationCounter].stopTime));

        route[stationCounter].station->setTrainToLeave(this);
        while(!this->isAllowedToLeave) {}

        InfoBuffer::getInstance()->pushMessage("Train " + std::to_string(getID()) + " left from track: " + std::to_string(getTrackAt()) + "\n", TOP_PRIORITY);

        this->setTrackAt(-1);
        this->setIsAllowedToLeave(false);
        this->stationCounter++;
        this->hasArrived = false;
    }

    InfoBuffer::getInstance()->pushMessage("Train: " + std::to_string(id) + " finished its route.\n");
}