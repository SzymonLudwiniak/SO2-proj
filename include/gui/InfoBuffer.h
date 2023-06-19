#pragma once

#include <vector>
#include <string>

#include "ViewPort.h"


class InfoBuffer : public ViewPort
{
public:
    InfoBuffer(float posX, float posY, int width, int height);
    InfoBuffer(fVec position, dVec size);

    bool pushMessage(std::string message, unsigned short priority = 3);

    bool draw();

private:
    std::vector<std::pair<std::string, unsigned short>> logs;

    unsigned int messageLimit;
};