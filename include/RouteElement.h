#pragma once

class Station;

struct RouteElement
{
    Station* station;
    int stopTime;
};