#pragma once

#include <vector>

#include "utility.h"
#include "ViewPort.h"


class Canva : public ViewPort
{
public:
    Canva(float posX, float posY, int width, int height);
    Canva(fVec position, dVec size);

    bool addComponent(Drawable * component);

    bool draw();

private:
    std::vector<Drawable*> components; 

    void adjustCompPos(Drawable * component);

    bool isInBounds(Drawable * component);
};
