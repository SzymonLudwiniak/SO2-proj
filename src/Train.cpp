#include "../include/Train.h"

std::atomic<int> Train::trainCounter = 0;

// int Train::operator<(const Train* other_)
// {
//     return other_->priority - this->priority;
// }