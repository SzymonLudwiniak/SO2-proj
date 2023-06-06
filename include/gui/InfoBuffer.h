#pragma once

#include <vector>
#include <string>

#include "Drawable.h"


class InfoBuffer : public Drawable
{
public:
    InfoBuffer(int posX, int posY, int width, int height);
    InfoBuffer(sVec position, sVec size);

    void setSize(sVec size);
    sVec getSize() const;

    bool pushMessage(std::string message, unsigned short priority = 3);

    bool draw();

private:
    std::vector<std::pair<std::string, unsigned short>> logs;

    sVec size;
    unsigned int messageLimit;

    void drawBounds();
};