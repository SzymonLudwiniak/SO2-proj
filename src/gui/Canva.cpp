#include "../../include/gui/Canva.h"


Canva::Canva(int posX, int posY, int width, int height)
{
    this->position.x = posX;
    this->position.y = posY;
    this->size.x = width;
    this->size.y = height;
}

Canva::Canva(sVec position, sVec size)
{
    this->position = position;
    this->size = size;
}

void Canva::setPosition(sVec pos)
{
    this->position = pos;
}

void Canva::setSize(sVec size)
{
    this->size = size;
}

sVec Canva::getPosition()
{
    return position;
}

sVec Canva::getSize()
{
    return size;
}

void Canva::addComponent(Drawable * component)
{
    components.push_back(component);
}