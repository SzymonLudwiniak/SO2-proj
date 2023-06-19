#include <ncurses.h>

#include "../../include/gui/Drawable.h"


void Drawable::moveBy(int x, int y)
{
    this->position.x += x;
    this->position.y += y;
}

void Drawable::moveBy(fVec vec)
{
    this->position.x += vec.x;
    this->position.y += vec.y;
}

void Drawable::setPosition(float x, float y)
{
    this->position.x = x;
    this->position.y = y;
}

void Drawable::setPosition(fVec position)
{
    this->position = position;
}

fVec Drawable::getPosition() const
{
    return position;
}

bool Drawable::draw()
{
    mvaddch(position.y, position.x, '@');
    return true;
}