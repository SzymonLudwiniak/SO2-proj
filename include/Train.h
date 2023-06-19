#pragma once

#include <string>
#include <vector>
#include <atomic>

#include "enums/SemaphoreEnum.h"
#include "gui/Drawable.h"
#include "gui/InfoBuffer.h"

struct RouteElement;


class Train : public Drawable
{
public:

    virtual void setNextSignal(SemaphoreEnum nextSignal_) = 0;
    virtual void run() = 0;

    virtual int getTrackAt() = 0;
    virtual int getID() = 0;

    virtual bool getIsAbleToLeave() = 0;

    virtual void setDriver(int driverID_) = 0;
    virtual void setTrackAt(int trackAt_) = 0;
    virtual void setIsAllowedToLeave(bool isAllowedToLeave_) = 0;

    bool operator<(const Train & other_);

protected:

    static std::atomic<int> trainCounter;

    int maxSpeed;
    int currentSpeed {0};

    std::atomic<int> priority;
    std::atomic<int> id;

    std::atomic<int> trackAt{-1};
    std::atomic<bool> isAbleToLeave{false};
    std::atomic<bool> isAllowedToLeave{false};

    std::atomic<SemaphoreEnum> nextSignal {SemaphoreEnum::GO_MAX_SPEED};

    std::string currentStation {""};

    std::vector<RouteElement> route;
    int stationCounter{0};

    int driverID{-1};

    bool hasArrived{false};

};