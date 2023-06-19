#pragma once

#include <string>

#include "ViewPort.h"


class PromptWindow : public ViewPort
{
public:
    PromptWindow(sVec position, sVec size);

    void setVisible(bool visible);
    void setString(std::string str);

    bool getVisible() const;
    std::string getString() const;

    bool draw();

private:
    bool visible;
    std::string str;

    void drawBounds();
};