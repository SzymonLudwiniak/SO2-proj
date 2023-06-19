#include <ncurses.h>
#include <cstring>

#include "../../include/gui/ViewPort.h"


void ViewPort::setSize(dVec size)
{
    this->size = size;
}

dVec ViewPort::getSize() const
{
    return size;
}


void ViewPort::drawBounds()
{
    attr_t currAttrs;
    short currPair;
    attr_get(&currAttrs, &currPair, NULL);

    attron(COLOR_PAIR(BORDER_COLOR));

    fVec pos = getPosition();
    move(pos.y, pos.x);
    hline('#', size.x);
    vline('#', size.y);
    move(pos.y+size.y, pos.x);
    hline('#', size.x+1);
    move(pos.y, pos.x+size.x);
    vline('#', size.y);

    attr_set(currAttrs, currPair, NULL);
}