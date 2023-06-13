#pragma once

#include <vector>

#include "utility.h"
#include "ViewPort.h"


class Canva : public ViewPort
{
public:
    Canva(int posX, int posY, int width, int height);
    Canva(sVec position, sVec size);

    bool addComponent(Drawable * component);

    bool draw();

private:
    std::vector<Drawable*> components; 

    void adjustCompPos(Drawable * component);

    bool isInBounds(Drawable * component);
};
