#pragma once

#include <vector>
#include <string>

#include "ViewPort.h"


class InfoBuffer : public ViewPort
{
public:
    InfoBuffer(int posX, int posY, int width, int height);
    InfoBuffer(sVec position, sVec size);

    bool pushMessage(std::string message, unsigned short priority = 3);

    bool draw();

private:
    std::vector<std::pair<std::string, unsigned short>> logs;

    unsigned int messageLimit;
};