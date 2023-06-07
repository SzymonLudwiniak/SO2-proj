#pragma once

#include <vector>
#include <queue>

#include "PassengerTrain.h"

class Station
{
public:
    
    Station(std::string name_, int tracksNum_, int platformsNum_);    

    void run();

    void setIsRouteFree(bool isRouteFree_);

    const std::string name;

    void addTrain(Train* train_);

private:

    std::vector<int> tracks;
    int platformsNum;

    std::vector<SemaphoreEnum> outSemaphores;

    std::priority_queue<Train*> trainsToLeave;
    std::queue<Train*> trainsToArrive;

    bool isRouteFree{true};
};