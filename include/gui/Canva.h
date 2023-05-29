#pragma once

#include <vector>

#include "utility.h"
#include "Drawable.h"


class Canva
{
public:
    Canva(int posX, int posY, int width, int height);
    Canva(sVec position, sVec size);

    void setPosition(sVec pos);
    void setSize(sVec size);

    sVec getPosition();
    sVec getSize();

    void addComponent(Drawable * component);

    void draw();

private:
    std::vector<Drawable*> components; 

    sVec position;
    sVec size;
};
