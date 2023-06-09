#pragma once

#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>

#include "PassengerTrain.h"
#include "gui/Drawable.h"

class Station : public Drawable
{
public:

    Station(std::string name_, int tracksNum_, int platformsNum_);

    ~Station();

    [[noreturn]] void leavingMechanism();

    [[noreturn]] void arrivingMechanism();

    void setIsRouteFree(bool isRouteFree_);
    bool getIsRouteFree();

    const std::string name;

    void addTrain(Train* train_);

    virtual bool draw();

private:

    void enqueue(Train* train_);
    Train* dequeue();
    void popQueue();
    void enqueuePriority(Train* train_);
    Train* dequeuePriority();
    void popPriority();

    std::priority_queue<Train*> trainsToLeave;
    std::queue<Train*> trainsToArrive;

    std::mutex trainsToLeaveMutex;
    std::mutex trainsToArriveMutex;

    std::atomic<bool> isRouteFree{true};

    int* tracks{nullptr};
    int tracksNum;
    int platformsNum;

};