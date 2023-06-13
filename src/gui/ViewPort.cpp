#include <ncurses.h>
#include <cstring>

#include "../../include/gui/ViewPort.h"


void ViewPort::setSize(sVec size)
{
    this->size = size;
}

sVec ViewPort::getSize() const
{
    return size;
}


void ViewPort::drawBounds()
{
    attr_t currAttrs;
    short currPair;
    attr_get(&currAttrs, &currPair, NULL);

    attron(COLOR_PAIR(BORDER_COLOR));

    sVec pos = getPosition();
    move(pos.y, pos.x);
    hline('#', size.x);
    vline('#', size.y);
    move(pos.y+size.y, pos.x);
    hline('#', size.x+1);
    move(pos.y, pos.x+size.x);
    vline('#', size.y);

    attr_set(currAttrs, currPair, NULL);
}