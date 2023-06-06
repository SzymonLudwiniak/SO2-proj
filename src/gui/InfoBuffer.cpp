#include <ncurses.h>
#include <cstring>

#include "../../include/gui/InfoBuffer.h"


InfoBuffer::InfoBuffer(int posX, int posY, int width, int height)
{
    setPosition({posX, posY});
    this->size.x = width;
    this->size.y = height;
    messageLimit = height-1;
}

InfoBuffer::InfoBuffer(sVec position, sVec size)
{
    setPosition(position);
    this->size = size;
    messageLimit = size.y-1;
}

void InfoBuffer::setSize(sVec size)
{
    this->size = size;
}

sVec InfoBuffer::getSize() const
{
    return size;
}

bool InfoBuffer::pushMessage(std::string message, unsigned short priority)
{
    logs.push_back({message, priority});
    if(logs.size() > messageLimit)
    {
        logs.erase(logs.begin());
        return true;
    }
    return false;
}

bool InfoBuffer::draw()
{
    sVec pos = getPosition();
    pos.y++;
    pos.x++;

    for(auto l : logs)
    {
        attr_t currAttrs;
        short currPair;
        attr_get(&currAttrs, &currPair, NULL);
        attron(COLOR_PAIR(l.second));

        char trunMess[size.x];
        trunMess[size.x-1] = '\0';

        strncpy(trunMess, l.first.c_str(), size.x-1);
        mvprintw(pos.y++, pos.x, trunMess);

        attr_set(currAttrs, currPair, NULL);
    }
    drawBounds();

    if(logs.empty())
        return false;
    return true;
}

void InfoBuffer::drawBounds()
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