#pragma once

#include "utility.h"


class Drawable 
{
public:
    void moveBy(int x, int y);
    void moveBy(fVec vec);

    void setPosition(float x, float y);
    void setPosition(fVec position);

    fVec getPosition() const;

    virtual bool draw();

private:
    fVec position;

};