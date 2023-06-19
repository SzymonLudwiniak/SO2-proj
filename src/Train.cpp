#include "../include/Train.h"

std::atomic<int> Train::trainCounter = 0;

bool Train::operator<(const Train & other_)
{
    return this->priority < other_.priority;
}