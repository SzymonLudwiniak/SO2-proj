#pragma once

#include "utility.h"


class Drawable 
{
public:
    void moveBy(int x, int y);
    void moveBy(sVec vec);

    void setPosition(int x, int y);
    void setPosition(sVec position);

    sVec getPosition() const;

    virtual bool draw();

private:
    sVec position;

};