#include "../../include/gui/Drawable.h"


void Drawable::moveBy(int32_t x, int32_t y)
{
    this->position.x += x;
    this->position.y += y;
}

void Drawable::moveBy(sCoord vec)
{
    this->position.x += vec.x;
    this->position.y += vec.y;
}

void Drawable::setPosition(int32_t x, int32_t y)
{
    this->position.x = x;
    this->position.y = y;
}

void Drawable::setPosition(sCoord position)
{
    this->position.x = position.x;
    this->position.y = position.y;
}

sCoord Drawable::getPosition() const
{
    return position;
}

bool Drawable::draw()
{
    return true;
}