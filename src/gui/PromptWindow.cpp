#include <ncurses.h>
#include <sstream>

#include "../../include/gui/PromptWindow.h"


PromptWindow::PromptWindow(sVec position, sVec size)
{
    setPosition(position);
    setSize(size);

    visible = false;
}

void PromptWindow::setVisible(bool visible)
{
    this->visible = visible;
}

void PromptWindow::setString(std::string str)
{
    this->str = str;
}

bool PromptWindow::getVisible() const
{
    return visible;
}

std::string PromptWindow::getString() const
{
    return str;
}

bool PromptWindow::draw()
{
    if(!visible)
        return false;
    drawBounds();

    if(str.empty())
        return true;

    sVec pos = getPosition();
    pos.x++;
    pos.y++;

    std::stringstream ss(str.c_str());
    std::string line;
    while(std::getline(ss, line, '\n'))
    {
        mvprintw(pos.y++, pos.x, "%s", line.c_str());
    }

    return true;
}

void PromptWindow::drawBounds()
{
    attr_t currAttrs;
    short currPair;
    attr_get(&currAttrs, &currPair, NULL);

    attron(COLOR_PAIR(REV_BASE_COLOR));

    sVec pos = getPosition();
    sVec size = getSize();
    move(pos.y, pos.x);
    hline('-', size.x);
    vline('|', size.y);
    move(pos.y+size.y, pos.x);
    hline('-', size.x+1);
    move(pos.y, pos.x+size.x);
    vline('|', size.y);
    mvprintw(pos.y, pos.x, "+");
    mvprintw(pos.y, pos.x + size.x, "+");
    mvprintw(pos.y + size.y, pos.x, "+");
    mvprintw(pos.y + size.y, pos.x + size.x, "+");

    attr_set(currAttrs, currPair, NULL);
}