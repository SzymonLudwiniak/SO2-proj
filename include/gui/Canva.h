#pragma once

#include <vector>

#include "utility.h"
#include "Drawable.h"


class Canva : public Drawable
{
public:
    Canva(int posX, int posY, int width, int height);
    Canva(sVec position, sVec size);

    void setSize(sVec size);
    sVec getSize() const;

    bool addComponent(Drawable * component);

    bool draw();

private:
    std::vector<Drawable*> components; 

    sVec size;

    void adjustCompPos(Drawable * component);
    void drawBounds();

    bool isInBounds(Drawable * component);
};
