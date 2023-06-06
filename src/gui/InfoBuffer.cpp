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

bool InfoBuffer::pushMessage(std::string message)
{
    messages.push_back(message);
    if(messages.size() > messageLimit)
    {
        messages.erase(messages.begin());
        return true;
    }
    return false;
}

bool InfoBuffer::draw()
{
    sVec pos = getPosition();
    pos.y++;
    pos.x++;

    for(auto m : messages)
    {
        char trunMess[size.x];
        trunMess[size.x-1] = '\0';

        strncpy(trunMess, m.c_str(), size.x-1);
        mvprintw(pos.y++, pos.x, trunMess);
    }
    drawBounds();

    if(messages.empty())
        return false;
    return true;
}

void InfoBuffer::drawBounds()
{
    sVec pos = getPosition();
    move(pos.y, pos.x);
    hline('#', size.x);
    vline('#', size.y);
    move(pos.y+size.y, pos.x);
    hline('#', size.x+1);
    move(pos.y, pos.x+size.x);
    vline('#', size.y);
}