#include "utility.h"


class Drawable 
{
public:
    void moveBy(int32_t x, int32_t y);
    void moveBy(sCoord vec);

    void setPosition(int32_t x, int32_t y);
    void setPosition(sCoord position);

    sCoord getPosition() const;

    virtual bool draw();

private:
    sCoord position;

};