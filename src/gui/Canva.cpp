#include <ncurses.h>

#include "../../include/gui/Canva.h"


Canva::Canva(int posX, int posY, int width, int height)
{
    setPosition({posX, posY});
    setSize({width, height});
}

Canva::Canva(sVec position, sVec size)
{
    setPosition(position);
    setSize(size);
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
    sVec p = getPosition();
    p.x += 1;
    p.y += 1;
    component->moveBy(p); // adjust position to canva
}

bool Canva::isInBounds(Drawable * component)
{
    sVec pos = getPosition();
    sVec cPos = component->getPosition();
    sVec size = getSize();

    if(cPos.x < pos.x || cPos.x > pos.x + size.x ||
        cPos.y < pos.y || cPos.y > pos.y + size.y)
        return false;
    return true;
}