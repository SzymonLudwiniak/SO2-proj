#include <algorithm>
#include <iostream>
#include <ncurses.h>

#include "../include/Station.h"
#include "../include/gui/InfoBuffer.h"


Station::Station(std::string name_, int tracksNum_, int platformsNum_)
        : name(name_),
          tracksNum(tracksNum_),
          platformsNum(platformsNum_),
          prompt({0, 0}, {10, tracksNum_+1})
{
    tracks = new int[tracksNum];
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

      //  trainToLeave->setNextSignal(SemaphoreEnum::GO_MAX_SPEED);
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
                for(int i = 0; i < platformsNum; i++)
                {
                    if(tracks[i] != -1)
                        continue;

                    trackToArrive = i;
                    tracks[i] = trainToArrive->getID();
                    InfoBuffer::getInstance()->pushMessage("train " + std::to_string(trainToArrive->getID()) + " is on track " + std::to_string(i));
                    break;
                }
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

      //  trainToArrive->setNextSignal(SemaphoreEnum::STOP);
        trainToArrive->setTrackAt(trackToArrive);
        popQueue();

      //  std::cout << "Train " << trainToArrive->getID() << " arrived on track: " << trainToArrive->getTrackAt() << "\n";
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

void Station::setTrainToLeave(Train* train_)
{
    enqueuePriority(train_);
}

bool Station::draw()
{
    fVec p = getPosition();
    prompt.setPosition(p.x-12, p.y-4);
    for(int y = 0; y < 3; y++)
        for(int x = 0; x < 3; x++)
            mvaddch(p.y+y, p.x+x, '#');
    
    if(prompt.getVisible())
    {
        std::string info = "";
        for(int t = 0; t < tracksNum; t++)
            info += "track: " + std::to_string(tracks[t]) + "\n";
        prompt.setString(info);
    }
    prompt.draw();
    return true;
}

void Station::enqueue(Train* train_)
{
    std::lock_guard<std::mutex> lock(trainsToArriveMutex);
    trainsToArrive.push(train_);
}

Train* Station::dequeue()
{
    std::lock_guard<std::mutex> lock(trainsToArriveMutex);
    return trainsToArrive.front();
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
    return trainsToLeave.top();
}

void Station::popPriority()
{
    std::lock_guard<std::mutex> lock(trainsToLeaveMutex);
    trainsToLeave.pop();
}

