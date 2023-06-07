#include <algorithm>
#include <iostream>

#include "../include/Station.h"

Station::Station(std::string name_, int tracksNum_, int platformsNum_)
  : name(name_), 
    tracks(tracksNum_, -1),
    platformsNum(platformsNum_),
    outSemaphores(tracksNum_, SemaphoreEnum::STOP)
{ }

void Station::run()
{
    while(true)
    {
        // check if track is empty if so
        // train leaves
        if(isRouteFree && !trainsToLeave.empty())
        {
            auto trainToLeave = trainsToLeave.top();
            
            std::cout << "Train left:" << trainToLeave->getID() << " from track: " << trainToLeave->getTrackAt() << "\n";

            trainToLeave->setNextSignal(SemaphoreEnum::GO_40KMH);

            tracks[trainToLeave->getTrackAt()] = -1; 
            trainToLeave->setTrackAt(-1);

            trainsToLeave.pop();
            
            this->isRouteFree = false;

            
        }

        if(trainsToArrive.empty())
            continue;

        auto trainToArrive = trainsToArrive.front();

        if(dynamic_cast<PassengerTrain*>(trainToArrive))
        {
            int trackToArrive = platformsNum;

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
            trainToArrive->setTrackAt(trackToArrive);
        }
        else
        {
            int trackToArrive = tracks.size();

            while(trackToArrive == tracks.size())
            {
                for(int i = 0; i < tracks.size(); i++)
                {
                    if(tracks[i] != -1)
                        continue;

                    trackToArrive = i;
                    tracks[i] = trainToArrive->getID();

                    break;
                }
            }   

            trainToArrive->setTrackAt(trackToArrive);
        }

        trainsToLeave.push(trainToArrive);
        trainsToArrive.pop();

        std::cout << "Train " << trainToArrive->getID() << " arrived:" << trainToArrive->getID() << " on track: " << trainToArrive->getTrackAt() << "\n";
    }
}

void Station::setIsRouteFree(bool isRouteFree_)
{
    this->isRouteFree = isRouteFree_;
}   

void Station::addTrain(Train* train_)
{
    trainsToArrive.push(train_);
}