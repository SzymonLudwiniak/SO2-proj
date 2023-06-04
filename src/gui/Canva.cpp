#include <ncurses.h>

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

bool Canva::addComponent(Drawable * component)
{
    if(component == nullptr)
        return false;

    components.push_back(component);
    adjustCompPos(component);
    return true;
}

bool Canva::draw()
{
    for(auto component : components)
    {
        if(!isInBounds(component))
           continue;    // component's not in bounds
        component->draw();
    }

    drawBounds();

    if(components.size() == 0)
        return false;
    return true;
}

void Canva::adjustCompPos(Drawable * component)
{
    sVec p = position;
    p.x += 1;
    p.y += 1;
    component->moveBy(p); // adjust position to canva
}

void Canva::drawBounds()
{
    move(position.y, position.x);
    hline('#', size.x);
    vline('#', size.y);
    move(position.y+size.y, position.x);
    hline('#', size.x+1);
    move(position.y, position.x+size.x);
    vline('#', size.y);
}

bool Canva::isInBounds(Drawable * component)
{
    sVec cPos = component->getPosition();
    if(cPos.x < position.x || cPos.x > position.x + size.x ||
        cPos.y < position.y || cPos.y > position.y + size.y)
        return false;
    return true;
}