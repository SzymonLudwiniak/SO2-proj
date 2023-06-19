#pragma once

#include "utility.h"
#include "Drawable.h"

class ViewPort : public Drawable
{
public:
    void setSize(dVec size);
    dVec getSize() const;

protected:
    virtual void drawBounds();

private:
    dVec size;
};