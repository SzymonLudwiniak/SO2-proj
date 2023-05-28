#pragma once

#include <vector>
#include <queue>

#include "Train.h"

class Station
{
public:

    const std::string name;

private:

    std::vector<int> tracks{-1};
    std::vector<int> platforms{-1};

    std::priority_queue<Train> trainsToGoOut;
    std::queue<Train> trainsToGoIn;


};