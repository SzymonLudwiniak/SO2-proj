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
    driverID = driverID_;
}

void PassengerTrain::setTrackAt(int trackAt_)
{
    trackAt = trackAt_;
}

void PassengerTrain::setIsAllowedToLeave(bool isAllowedToLeave_)
{
    isAllowedToLeave = isAllowedToLeave_; 
}

void PassengerTrain::run()
{
    while(stationCounter < (int) route.size())
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
        if(trackAt == -1)
            continue;

        // dopoki jest przy peronie
        while(trackAt != -1)
        {
            // wymienił pasazerów, czeka na odjazd
            if(route[stationCounter].hasStoped)
                continue;
            
            isAbleToLeave = false;

            currentStation = route[stationCounter].stationName;

          //  std::cout << "Train: " << id << " stayed at station: " << currentStation << " platform: " << trackAt << " for: " << route[stationCounter].stopTime << "\n";

            std::this_thread::sleep_for(std::chrono::milliseconds(route[stationCounter].stopTime));
            
       //     std::cout << "Train " << id << " is ready to leave from: " << currentStation << "\n";
            
            currentStation = "";

            route[stationCounter].hasStoped = true;
            isAbleToLeave = true;

            
        }

        while(!isAllowedToLeave)
        {
            stationCounter++;
            isAllowedToLeave = false;
        }
        
    }

  //  std::cout << "Train: " << id << " finished its route.\n";
}