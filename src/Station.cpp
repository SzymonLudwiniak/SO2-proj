#include <algorithm>
#include <iostream>

#include "../include/Station.h"

Station::Station(std::string name_, int tracksNum_, int platformsNum_)
  : name(name_), 
    tracksNum(tracksNum_),
    platformsNum(platformsNum_)
{
    tracks = new std::atomic<int>[tracksNum];
    for(int i = 0; i < tracksNum; i++)
    {
        tracks[i] = -1;
    }
}

Station::~Station()
{
    delete[] tracks;
    tracks = nullptr;
}

void Station::leavingMechanism()
{
    while(true)
    {
        // check if track is empty if so
        // train leaves
        if(isRouteFree && !trainsToLeave.empty())
        {
            auto trainToLeave = dequeuePriority();

            while(!trainToLeave->getIsAbleToLeave()) {}
            
            std::cout << "Train left:" << trainToLeave->getID() << " from track: " << trainToLeave->getTrackAt() << "\n";

            tracks[trainToLeave->getTrackAt()] = -1; 
            trainToLeave->setTrackAt(-1);

            trainToLeave->setNextSignal(SemaphoreEnum::GO_40KMH);
            trainToLeave->setIsAllowedToLeave(true);
            
            this->isRouteFree = false; 
        }
    }
}

void Station::arrivingMechanism()
{
    while(true)
    {
        if(trainsToArrive.empty())
            continue;

        auto trainToArrive = dequeue();

        int trackToArrive = 0;

        if(dynamic_cast<PassengerTrain*>(trainToArrive))
        {
            trackToArrive = platformsNum;

            while(trackToArrive == platformsNum)
            {
                for(int i = 0; i < platformsNum; i++)
                {
                    if(tracks[i] != -1)
                        continue;

                    trackToArrive = i;
                    tracks[i] = trainToArrive->getID();

                    break;
                }
            }    
        }
        else
        {
            trackToArrive = tracksNum;

            while(trackToArrive == tracksNum)
            {
                for(int i = 0; i < tracksNum; i++)
                {
                    if(tracks[i] != -1)
                        continue;

                    trackToArrive = i;
                    tracks[i] = trainToArrive->getID();

                    break;
                }
            }   
        }

        trainToArrive->setNextSignal(SemaphoreEnum::STOP);
        trainToArrive->setTrackAt(trackToArrive);

        enqueuePriority(trainToArrive);
        dequeue();

        std::cout << "Train " << trainToArrive->getID() << " arrived:" << trainToArrive->getID() 
            << " on track: " << trainToArrive->getTrackAt() << "\n";
    }
}

void Station::setIsRouteFree(bool isRouteFree_)
{
    this->isRouteFree = isRouteFree_;
}   

void Station::addTrain(Train* train_)
{
    enqueue(train_);
}

void Station::enqueue(Train* train_)
{
    std::lock_guard<std::mutex> lock(trainsToArriveMutex);
    trainsToArrive.push(train_);
}

Train* Station::dequeue()
{
    std::lock_guard<std::mutex> lock(trainsToArriveMutex);
    auto train = trainsToArrive.front();
    trainsToArrive.pop();
    return train;
}

void Station::enqueuePriority(Train* train_)
{
    std::lock_guard<std::mutex> lock(trainsToLeaveMutex);
    trainsToLeave.push(train_);
}

Train* Station::dequeuePriority()
{
    std::lock_guard<std::mutex> lock(trainsToLeaveMutex);
    auto train = trainsToLeave.top();
    trainsToLeave.pop();
    return train;
}