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

    bool pushMessage(std::string message);

    bool draw();

private:
    std::vector<std::string> messages;

    sVec size;
    unsigned int messageLimit;

    void drawBounds();
};