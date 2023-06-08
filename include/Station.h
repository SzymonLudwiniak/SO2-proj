#pragma once

#include <vector>
#include <queue>
#include <mutex>

#include "PassengerTrain.h"

class Station
{
public:
    
    Station(std::string name_, int tracksNum_, int platformsNum_);    

    ~Station();

    void leavingMechanism();
    void arrivingMechanism();

    void setIsRouteFree(bool isRouteFree_);

    const std::string name;

    void addTrain(Train* train_);

private:

    void enqueue(Train* train_);
    Train* dequeue();
    void enqueuePriority(Train* train_);
    Train* dequeuePriority();


    std::priority_queue<Train*> trainsToLeave;
    std::queue<Train*> trainsToArrive;

    std::mutex trainsToLeaveMutex;
    std::mutex trainsToArriveMutex;

    bool isRouteFree{true};

    std::atomic<int>* tracks{nullptr};
    int tracksNum;
    int platformsNum;
    
};