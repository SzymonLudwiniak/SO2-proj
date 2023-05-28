#include "../include/Driver.h"

Driver::Driver(int id_) 
    : id(id_)
{ }

int Driver::getID() const
{
    return this->id;
}