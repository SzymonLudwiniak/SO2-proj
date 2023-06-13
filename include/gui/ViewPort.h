#pragma once

#include "utility.h"
#include "Drawable.h"

class ViewPort : public Drawable
{
public:
    void setSize(sVec size);
    sVec getSize() const;

protected:
    virtual void drawBounds();

private:
    sVec size;
};