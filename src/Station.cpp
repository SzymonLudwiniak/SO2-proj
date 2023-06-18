#include <algorithm>
#include <iostream>

#include "../include/Station.h"

Station::Station(std::string name_, int tracksNum_, int platformsNum_)
        : name(name_),
          tracksNum(tracksNum_),
          platformsNum(platformsNum_)
{
    tracks = new int[tracksNum];
    for(int i = 0; i < tracksNum; i++)
    {
        tracks[i] = -1;
    }

    std::cout << "track status:\n";
    for(int i = 0; i < tracksNum; i++)
    {
        std::cout << "track " << i << " train id: " << tracks[i] << "\n";
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

        if(!isRouteFree)
        {
            continue;
        }

        if(trainsToLeave.empty())
        {
            continue;
        }

        auto trainToLeave = dequeuePriority();

        tracks[trainToLeave->getTrackAt()] = -1;

        trainToLeave->setNextSignal(SemaphoreEnum::GO_40KMH);
        trainToLeave->setIsAllowedToLeave(true);

        this->isRouteFree = false;

        popPriority();
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
                // std::cout << "track status: for train " << trainToArrive->getID() << "\n";
                // for(int i = 0; i < tracksNum; i++)
                // {
                //     std::cout << "track " << i << " train id: " << tracks[i] << "\n";
                // }

                for(int i = 0; i < platformsNum; i++)
                {
                    if(tracks[i] != -1)
                        continue;

                    trackToArrive = i;
                    tracks[i] = trainToArrive->getID();

                    break;
                }

                // std::cout << "track status after train " << trainToArrive->getID() << "\n";
                // for(int i = 0; i < tracksNum; i++)
                // {
                //     std::cout << "track " << i << " train id: " << tracks[i] << "\n";
                // }
            }
        }
        else
        {
            trackToArrive = tracksNum;

            while(trackToArrive == tracksNum)
            {
                for(int i = platformsNum; i < tracksNum; i++)
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
        popQueue();

        std::cout << "Train " << trainToArrive->getID() << " arrived:" << trainToArrive->getID()
                  << " on track: " << trainToArrive->getTrackAt() << "\n";
    }
}

void Station::setIsRouteFree(bool isRouteFree_)
{
    this->isRouteFree = isRouteFree_;
}

bool Station::getIsRouteFree()
{
    return isRouteFree;
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
    return train;
}

void Station::popQueue()
{
    std::lock_guard<std::mutex> lock(trainsToArriveMutex);
    trainsToArrive.pop();
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
    //trainsToLeave.pop();
    return train;
}

void Station::popPriority()
{
    std::lock_guard<std::mutex> lock(trainsToLeaveMutex);
    trainsToLeave.pop();
}
