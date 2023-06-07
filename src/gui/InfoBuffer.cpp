#include <ncurses.h>
#include <cstring>

#include "../../include/gui/InfoBuffer.h"


InfoBuffer::InfoBuffer(int posX, int posY, int width, int height)
{
    setPosition({posX, posY});
    setSize({width, height});
    messageLimit = height-1;
}

InfoBuffer::InfoBuffer(sVec position, sVec size)
{
    setPosition(position);
    setSize(size);
    messageLimit = size.y-1;
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
    sVec size = getSize();
    pos.y++;
    pos.x++;

    char clearingBuffer[getSize().x];
    memset(clearingBuffer, ' ', size.x*sizeof(*clearingBuffer));
    clearingBuffer[size.x - 1] = '\0';

    for(auto l : logs)
    {
        attr_t currAttrs;
        short currPair;
        attr_get(&currAttrs, &currPair, NULL);
        attron(COLOR_PAIR(l.second));

        char trunMess[size.x];
        trunMess[size.x-1] = '\0';

        strncpy(trunMess, l.first.c_str(), size.x-1);

        mvprintw(pos.y, pos.x, "%s", clearingBuffer);
        mvprintw(pos.y++, pos.x, "%s", trunMess);

        attr_set(currAttrs, currPair, NULL);
    }
    drawBounds();

    if(logs.empty())
        return false;
    return true;
}